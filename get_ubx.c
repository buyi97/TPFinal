#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "status.h"
#include "estructuras.h"

#define SYNC_CHAR1 0xB5
#define SYNC_CHAR2 0X62
#define SHIFT_BYTE 8

typedef unsigned char uchar; 

status_t get_ubx(ubx_t *ubx, bool *eof, FILE *fin);
status_t find_sync_chars_ubx(bool *eof, FILE *fin);
status_t fread_err(bool *eof, FILE *fin);

/*main para testear	
int main (void){
	ubx_t ubx;
	bool eof;

	get_ubx(&ubx, &eof, stdin);

	return EXIT_SUCCESS;
}*/

status_t get_ubx(ubx_t *ubx, bool *eof, FILE *fin){
	status_t st;
	size_t size_t_aux = 0;
	
	/*punteros no nulos*/
	if(!fin || !ubx	|| !eof)
		return ST_ERR_PUNT_NULL;

	eof = false;

	/*mueve el puntero del archivo de entrada hasta el lugar siguiente a los caracteres de sincronismo o hasta EOF */
	if((st = find_sync_chars_ubx(eof, fin)) != ST_OK)
		return st;

	/*carga los campos de la estructura*/
	if(!eof){

		/*carga clase*/
		if(fread(&ubx->clase, 1, 1, fin) != 1){
   				return fread_err(eof, fin);
			}

		/*carga id*/
		if(fread(&ubx->id, 1, 1, fin) != 1){
   				return fread_err(eof, fin);
			}

		/*lee y convierte "largo" de little endian a size_t*/
		ubx->largo = 0;
		if(fread(&size_t_aux, 1, 1, fin) != 1){
   				return fread_err(eof, fin);
			} 
		if(fread(&ubx->largo, 1, 1, fin) != 1){
   				return fread_err(eof, fin);
			}
		ubx->largo <<= SHIFT_BYTE;
		ubx->largo |= size_t_aux; /*largo cargado a la estructura*/

		/*asigna memoria para *payload */
		ubx->payload = (uchar *) malloc((ubx->largo + 1)*sizeof(uchar));
		if(!ubx->payload){
			return ST_ERR_NO_MEMORIA;	
		}

		ubx->payload[ubx->largo] = '\0';
		
		/*carga payload*/
		if(fread(ubx->payload, 1, ubx->largo, fin) != ubx->largo){
   				return fread_err(eof, fin);
			}

		/*carga el checksum*/
		if(fread(&ubx->ck_a, 1, 1, fin) != 1){
   				return fread_err(eof, fin);
			}
		if(fread(&ubx->ck_b, 1, 1, fin) != 1){
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
