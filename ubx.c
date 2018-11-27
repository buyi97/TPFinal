#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "status.h"
#include "ubx.h"

int main (void){
	uchar *sentencia;
	bool eof = false;
	FILE *fin,
	     *fout;
	int i=0;
	
	fin = fopen("UBXtest.txt", "rb");
	fout = fopen("prueba.txt", "wb");

	while(!eof){
		readline_ubx(&sentencia, &eof, fin);
		if(!eof){
			i++;
			fwrite(sentencia, 1, 98, fout);
		}
	}

	printf("se leyeron %d setencias UBX.\n", i);
 
	fclose(fin);
	fclose(fout);

	return EXIT_SUCCESS;
}

proc_nav_pvt(const char * sentencia, nav_pvt_t * pvt){
	if(!sentencia || !pvt){
		/*IMPRIMIR LOG*/
		return ST_ERR_PUNT_NULL;
	}

	/*carga el estado del fix*/
	pvt->type.pvt.gns_fix_ok =

	/*carga el posicionamiento*/
	pvt->type.pvt.latitud = 
	pvt->type.pvt.longitud =
	pvt->type.pvt.elevacion = (int) letol(sentencia, PVT_ELEVACION_POS, len);
	
	/*carga la fecha*/
	pvt->type.pvt.fecha.year = (int) letol(sentencia, PVT_YEAR_POS, len);
	pvt->type.pvt.fecha.month = (int) letol(sentencia, PVT_MONTH_POS, len);
	pvt->type.pvt.fecha.day = (int) letol(sentencia, PVT_DAY_POS, len);
	
	/*carga la hora*/
	pvt->type.pvt.hora.hh = (int) letol(sentencia, PVT_HH_POS, len);
	pvt->type.pvt.hora.mm = (int) letol(sentencia, PVT_MM_POS, len);
	pvt->type.pvt.hora.ss =

	return ST_OK;
}
proc_tim_tos(const char * sentencia, nav_pvt_t * pvt){
	if(!sentencia || !pvt){
		/*IMPRIMIR LOG*/
		return ST_ERR_PUNT_NULL;
	}

	/*carga la fecha*/
	pvt->type.tim_tos.fecha. =
	pvt->type.tim_tos.fecha. =
	pvt->type.tim_tos.fecha. =
	
	/*carga la hora*/
	pvt->type.tim_tos.hora. =
	pvt->type.tim_tos.hora. =
	pvt->type.tim_tos.hora. =

	return ST_OK;
}

proc_nav_posllh(const char * sentencia, nav_pvt_t * pvt){
	if(!sentencia || !pvt){
		/*IMPRIMIR LOG*/
		return ST_ERR_PUNT_NULL;
	}


}

/*Si el archivo tiene una sentencia UBX la función la carga en el buffer y devuelve un puntero "sentencia" al principio de la misma (no incluye los caracteres de sincronismo). Cuando el archivo se termina y no se encontraron sentencias devuelve eof=true y sentencia=NULL*/
status_t readline_ubx(uchar ** sentencia, bool * eof, FILE * fin){
	static uchar buffer[BUFFER_LEN];
	 static bool buffer_empty = true;

	/*punteros no nulos*/
	if(!sentencia || !eof || !fin){
		/*IMPRIMIR LOG*/
		return ST_ERR_PUNT_NULL;
	}

	/*carga inicial del buffer*/
	if(buffer_empty){
		fread_grind(buffer, 1, BUFFER_LEN, fin, eof);
		buffer_empty = false;
	}

	*eof = false;

	/*busca y devuelve sentencias UBX validadas hasta llegar a EOF*/
	while(get_sentence(buffer, eof, fin)){   
		if(checksum(buffer)){   
			*sentencia = buffer;
			return ST_OK;
		}else{
			/*IMPRIMIR LOG*/
		}
	}
	
	/*si salió del while es porque no hay más sentencias*/
	*sentencia = NULL;
	*eof=true;
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
	if(feof(fin)){
		*eof = true;
		return false;
	}

	/*si salió del 'for' y no se terminó el archivo mueve los dos ultimos bytes al principio del buffer y vuelve a empezar*/
	load_buffer(buffer, BUFFER_LEN-2, eof, fin);
	return get_sentence(buffer, eof, fin);	
}

/*borra los bytes que se encuentran antes de la posición 'pos' y carga la misma cantidad al final del buffer leyendo del archivo. 'pos' queda ubicado al principo del buffer*/
void load_buffer(uchar * buffer, size_t pos, bool * eof, FILE * fin){
	int i;

	/*mueve la sentencia al principio del buffer*/
	for(i = 0 ; i < BUFFER_LEN-pos ; i++){
		buffer[i] = buffer[pos + i];
	}

	
	/*sobreescribe la parte final del buffer*/
	fread_grind(buffer + BUFFER_LEN - pos, 1, pos, fin, eof);
	return;
}

/*lee del archivo y sobreescribe la parte final del buffer */
void fread_grind(void *ptr, size_t size, size_t nmemb, FILE *stream, bool * eof){
	if(fread(ptr, size, nmemb, stream) != nmemb){ 
			if (ferror(stream)){
				/*IMPRIMIR LOG*/
			}
			if(feof(stream)){ 
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
	long largo = 0;
	int i;
	
	/*lee el largo*/
	largo = letol(buffer, POS_LARGO, LEN_LARGO);
	
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
	if (ck_a == buffer[i++] && ck_b == buffer[i]){ /*al finalizar el 'for' anterior la posición 'i' corresponde al primer caracter de sincronismo*/
		return true;
	}else{
		return false;	
	}	
}

/*convierte de little-endian a entero*/
ulong letol(const uchar *string, size_t pos, size_t len){
	ulong entero = 0;
	int i;

	for(i = 0 ; i < len ; i++)
		entero |= string[pos + i] << SHIFT_BYTE*i;

	return entero;
}

/* convierte un decimal expresado en Estándar IEEE 754 a float */
double lotof(ulong entero){
	int i,
		signo = 0,
		exponente = 0,
		mantisa_int = 0; 
	double decimal,
		   mantisa_double = 1;/*se inicializa con el bit implícito*/

	/* lee el signo */
	signo = (entero & MASK_SIGNO) >> SHIFT_SIGNO;
	if(signo==1){
		signo = -1;
	}else{
		signo = 1;
	}

	/*lee el exponente*/
	exponente = (entero & MASK_EXPONENTE) >> SHIFT_EXPONENTE;
	exponente -= 127;

	/*lee la mantisa*/
	mantisa_int = entero & MASK_MANTISA;
	for(i = 0 ; i < 23 ; i++){
		if((mantisa_int>>(22-i))&1)
			mantisa_double += ldexp(1, -i - 1);
	}
	
	/*calcula el valor en punto flotante */
	decimal = signo * ldexp(mantisa_double, exponente);

	return decimal;
}
