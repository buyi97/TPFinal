#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "status.h"
#include "estructuras.h"

#define BUFFER_LEN 400 /*La longitúd del arreglo debe ser mayor a la máxima longitud posible para una sentencia UBX*/
#define SYNC_CHAR1 0xB5
#define SYNC_CHAR2 0X62
#define SHIFT_BYTE 8
#define LARGO_LEN 2 
#define POS_PAYLOAD 4

typedef unsigned char uchar; 

bool readline_ubx(uchar ** sentencia, bool * eof, FILE * fin);
bool get_sentence(uchar * buffer, bool * eof, FILE * fin);
void load_buffer(uchar * buffer, size_t pos, bool * eof, FILE * fin);
void fread_grind(void *ptr, size_t size, size_t nmemb, FILE *stream, bool * eof);
bool checksum(const uchar *buffer);

/*Si el archivo tiene una sentencia UBX la función la carga en el buffer y devuelve un puntero "sentencia" al principio de la misma (no incluye los caracteres de sincronismo). Cuando el archivo se termina y no se encontraron sentencias devuelve eof=true y sentencia=NULL*/
status_t readline_ubx(uchar ** sentencia, bool * eof, FILE * fin){
	static uchar buffer[BUFFER_LEN];

	/*punteros no nulos*/
	if(!sentencia || !eof || !fin){
		/*IMPRIMIR LOG*/
		return ST_ERR_PUNT_NULL;
	}

	*eof = false;

	while(get_sentence(buffer, eof, fin)){
		if(checksum(buffer)){
			*sentencia = buffer;
			return ST_OK;
		}else{
			/*IMPRIMIR LOG*/
		}	
	}

	*sentencia = NULL;
	return ST_OK;
}

/*busca una sentencia UBX y la mueve al principio del buffer (no incluye los caracteres de sincronismo)*/
bool get_sentence(uchar * buffer, bool * eof, FILE * fin){
	int i = 0;

	/*busca los dos caracteres de sincronismo en el buffer excepto en los dos últimos bytes*/
	for(i = 0 ; i < BUFFER_LEN-2 ; i++){
		if(buffer[i] == SYNC_CHAR1){
			if(buffer[i + 1] == SYNC_CHAR2){
				/*mueve la sentencia al principio del buffer*/
				load_buffer(buffer, i + 2, eof, fin);
				return true;
			}	
		}		
	}

	/*si salió del 'for' y se terminó el archivo es porque no hay más sentencias para leer*/
	if(eof)
		return false;

	/*si salió del 'for' y no se terminó el archivo mueve los dos ultimos bytes al principio del buffer y vuelve a empezar*/
	load_buffer(buffer, BUFFER_LEN-2, eof, fin);
	return get_sentence(buffer, eof, fin);	
}

/*borra los bytes que se encuentran antes de la posición 'pos' y carga la misma cantidad al final del buffer leyendo del archivo. 'pos' queda ubicado al principo del buffer*/
void load_buffer(uchar * buffer, size_t pos, bool * eof, FILE * fin){
	
	for(i = 0 ; i < BUFFER_LEN-pos ; i++){
		buffer[i] = buffer[pos + i];
	}

	fread_grind(buffer, 1, pos, fin, eof);
			
	return;
}

/*lee del archivo y modifica el puntero 'eof' cuando el archivo se termina*/
void fread_grind(void *ptr, size_t size, size_t nmemb, FILE *stream, bool * eof){
	if(fread(ptr, size, nmemb, stream) != nmemb){ 
			if (ferror(fin)){
				/*IMPRIMIR LOG*/
			}
			if(feof(fin)){
    				*eof = true; 
				/*IMPRIMIR LOG*/
			}
	}
	return;
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
	if(largo > BUFFER_LEN)
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
