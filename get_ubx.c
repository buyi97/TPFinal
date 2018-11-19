#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "status.h"
#include "estructuras.h"

#define SYNC_CHAR1 0xB5
#define SYNC_CHAR2 0x62
#define SHIFT_BYTE 8
#define LONGITUD_FIJA 6 /*campos de longitud fija incluyendo el checksum*/
#define POS_LARGO 2

typedef unsigned char uchar;

status_t readline_ubx(uchar **ubx, bool *eof, FILE *fin);
status_t find_sync_chars_ubx(bool *eof, FILE *fin);
status_t fread_err(bool *eof, FILE *fin);

/*main para testear	
int main (void){
	uchar *ubx;
	bool eof;

	readline_ubx(&ubx, &eof, stdin);

	return EXIT_SUCCESS;
}*/

/*lee una sentencia ubx del archivo */
status_t readline_ubx(uchar **ubx, bool *eof, FILE *fin){
	status_t st;
	size_t largo= 0;
	uchar * aux;
	
	/*punteros no nulos*/
	if(!fin || !ubx	|| !eof)
		return ST_ERR_PUNT_NULL;

	eof = false;

	/*mueve el puntero del archivo de entrada hasta el lugar siguiente a los caracteres de sincronismo o hasta EOF */
	if((st = find_sync_chars_ubx(eof, fin)) != ST_OK)
		return st;

	/*carga la sentencia ubx*/
	if(!eof){
		/*asigna memoria inicial*/
		*ubx = (uchar *) malloc(LONGITUD_FIJA*sizeof(uchar));
		if(!*ubx){
				return ST_ERR_NO_MEMORIA;	
		}

		/*carga campos de longitud fija*/
		if(fread(*ubx, 1, LONGITUD_FIJA, fin) != LONGITUD_FIJA){
   			return fread_err(eof, fin);
			}

		/*convierte largo de little endian a size_t*/
		largo = (*ubx)[POS_LARGO+1];
		largo <<= SHIFT_BYTE;
		largo |= (*ubx)[POS_LARGO];

		/*asigna memoria para payload*/
		aux = (uchar *) realloc(*ubx, (LONGITUD_FIJA + largo + 1)*sizeof(uchar));
		if(!aux){
			return ST_ERR_NO_MEMORIA;	
		}
		*ubx = aux;
		*ubx[LONGITUD_FIJA + largo]= '\0';

		/*lee el resto de la sentencia ubx*/
		if(fread(*ubx + LONGITUD_FIJA, 1, largo, fin) != largo){
   			return fread_err(eof, fin);
			}
	}

	return ST_OK;
}

/*mueve el puntero del archivo de entrada hasta el lugar siguiente a los caracteres de sincronismo o hasta EOF */
status_t find_sync_chars_ubx(bool *eof, FILE *fin){
	uchar aux;
	
	/*punteros no nulos*/
	if(!fin || !eof)
		return ST_ERR_PUNT_NULL;

	*eof = false;

	/*busca los dos caracteres de sincronismo*/
	while (fread(&aux, 1, 1, fin) == 1){				
		while(aux == SYNC_CHAR1){
			if(fread(&aux, 1, 1, fin) != 1){
   				return fread_err(eof, fin);
			}
			if(aux == SYNC_CHAR2){
				return ST_OK;
			}	
		}
	}

	return fread_err(eof, fin);
}

status_t fread_err(bool *eof, FILE *fin){
	if(feof(fin)){
    	*eof = true;
		return ST_OK;
	}else{
		return ST_IOERROR;	
	}		
}
