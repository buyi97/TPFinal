#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "status.h"
#include "estructuras.h"

#define STR_LEN 400 /*La longitúd del arreglo debe ser mayor a la máxima longitud posible para una sentencia UBX*/
#define SYNC_CHARS "µb" /*caracteres de sincronismo en formato ASCII*/ 
#define SHIFT_BYTE 8
#define SIZE_OF_SYNC_CHARS 2
#define LARGO_LEN 2 
#define POS_PAYLOAD 4

typedef unsigned char uchar; 

status_t readline_ubx(char * buffer, bool * eof, FILE * fin);
bool checksum(const uchar const *buffer);

/*main para testear con NAV-PVT*/
int main (void){
	char buffer[STR_LEN];
	char buffer2[98];
	bool eof = false;
	FILE *fin,
	     *fout;
	
	fin = fopen("UBXtest.txt", "rb");
	fout = fopen("prueba.txt", "wt");

	while(!eof){
		readline_ubx(buffer, &eof, fin);
		if(!eof){
			strncpy(buffer2, buffer, 98);
			fprintf(fout, "%s\n",buffer2);

		}
	}

	fclose(fin);
	fclose(fout);

	return 1;
}

/*Si el archivo tiene una sentencia UBX el programa la carga en el buffer. Cuando el archivo se termina y no se encontraron sentencias devuelve eof=true por interfaz. El largo de buffer debe ser STR_LEN, se puede validar en la primera linea con un sizeof pero mejor aclararlo como precondición y listo*/
status_t readline_ubx(char * buffer, bool * eof, FILE * fin){
	char * ptrsync_char;
	size_t diferencia;

	/*punteros no nulos*/
	if(!buffer || !eof || !fin){
		/*IMPRIMIR LOG*/
		return ST_ERR_PUNT_NULL;
	}

	*eof = false;

	/*busca los caracteres de sincronismo y guarda su posición en ptrsync_char*/
	while((ptrsync_char = strstr(buffer, SYNC_CHARS)) == NULL && *eof == false){
		if(fread(buffer, 1, STR_LEN, fin) != STR_LEN){ /*si no encontró los caracteres vuelve a leer del archivo*/
			if (ferror(fin)){
				/*IMPRIMIR LOG*/
			}
			if(feof(fin)){
    				*eof = true; /*después de esta asignación busca los caracteres de sincronismo una vez más antes de salir del while*/
				/*IMPRIMIR LOG*/
			} 
		}
	}

	/*si salió del while y el puntero es NULL es porque se terminó el archivo y no hay más caracteres de sincronismo cargados en el vector 'buffer'*/
	if(!ptrsync_char){
		return ST_OK;
	}

	/*mueve el puntero hacia un lugar después de los caracteres de sincronismo*/
	ptrsync_char += SIZE_OF_SYNC_CHARS;

	/*calcula el espacio inicial del vector donde no se encontraron caracteres de sincronismo*/
	diferencia = STR_LEN - sizeof(ptrsync_char);

	/*mueve la sentencia al principio del vector 'buffer' ingresado como parámetro*/
	strcpy(buffer, ptrsync_char);

	/*completa el espacio sobrante al final del vector 'buffer' leyendo del archivo*/
	if(fread(buffer + (STR_LEN - diferencia), 1, diferencia, fin) != diferencia){
			if (ferror(fin)){
				/*IMPRIMIR LOG*/
			}
			if(feof(fin)){
    				*eof = true;
				/*IMPRIMIR LOG*/
			} 
	}

    if (checksum((uchar *) buffer)) /*cast a uchar para llamar a la función checksum que trabaja con operadores de bits*/
    	return ST_OK; 
    
    if(eof && (ptrsync_char = strstr(buffer, SYNC_CHARS)) == NULL) /*si se terminó el archivo y no hay más caracteres de sincronismo cargados en el vector 'buffer' retorna ST_OK*/
    	return ST_OK;

   return readline_ubx(buffer, eof, fin); /*si el checksum no concuerda sigue buscando caracteres de sincronismo desde el lugar siguiente a dónde encontro los anteriores. No se pierde información de posibles sentencias válidas incluidas en el espacio que ocupaba la sentencia inválida. Recursividad de cola y todo el mundo contento*/
}

/*calcula el checksum*/
bool checksum(const uchar *buffer){
	uchar ck_a = 0,
	      ck_b = 0;
	size_t largo = 0;
	int i;
	
	/*pasa el largo del payload de little-endian a size_t*/
	for(i = 0 ; i < LARGO_LEN ; i++){
		largo <<= SHIFT_BYTE;
		largo |= buffer[POS_PAYLOAD - 1 - i];
	}

	/*si el largo leído es mayor a la máxima longitud de una sentencia UBX hay un error en la sentencia*/
	if(largo > STR_LEN)
		/*IMPRIMIR LOG*/
		return false;

	/*Calcula el checksum*/
	for(i = 0 ; i < (POS_PAYLOAD + largo) ; i++){
		ck_a = ck_a + buffer[i];
		ck_b = ck_b + ck_a;
	}

	/*compara el checksum calculado*/
	if (ck_a == buffer[i++] && ck_b == buffer[i]) /*al finalizar el 'for' anterior la posición 'i' corresponde al primer caracter de sincronismo*/
		return true;
	else
		return false;
}
