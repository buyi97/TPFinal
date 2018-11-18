/**
* @file str2hora.c
* @Author buyi97
* @date 18/11/2019
* @brief Pasar de una cadena hhmmss.ss a hora_t
*/

#include <stdio.h>
#include <string.h>
#include "fecha.h"

/**
* @brief Pasar de una cadena hhmmss.ss a hora_t
* @param Cadena hhmmss.ss, estructura hora_t;
* @return El estado en el que terminó la función (si fue todo bien ST_OK)
*/

status_t str2hora(char* cadena, struct hora_t* hora){
	
	char* ctemp;				
	double ntemp;
	
	if ( !cadena | !hora)
		return ST_ERR_PUNT_NULL;
	
	ntemp = strtod(cadena, &ctemp);

	if ( *ctemp != '\0' )
		return ST_ERR_HORA_INVALIDA;

	if ( (hora->hh = (int)ntemp/10000) < 0 ||  hora->hh > 23 ) 	  /*me fijo que sea hora valida entre 0 y 23*/
		return ST_ERR_HORA_INVALIDA;

	ntemp -= hora->hh*10000; 									/*le saco las horas*/

	if ( (hora->mm = (int)ntemp/100) < 0 || hora->mm > 59)        /*me fijo que sea minutos validos entre 0 y 59*/
		return ST_ERR_HORA_INVALIDA;

	ntemp -= hora->mm*100;  // le saco los minutos

	if ( (hora->ss = ntemp) < 0 || hora->ss > 59  ) 		/*me fijo que sean segundos validos entre 0 y 59*/
		return ST_ERR_HORA_INVALIDA;
		
	return ST_OK;
}
