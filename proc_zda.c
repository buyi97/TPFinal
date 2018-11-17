/**
* @file proc_zda.c
* @Author buyi97
* @date 17/11/2019
* @brief Procesar una cadena ZDA (del protocolo NMEA)
*/

#include "nmea.h"

/**
* @brief Cargar en una estructura los datos de ZDA a partir de una cadena
* @param Cadena ZDA, estructura nmea;
* @return El estado en el que terminé la función (si fue todo bien ST_OK)
*/

#define NMEA_ZDA_HORA_POS	1
#define NMEA_ZDA_DIA_POS	2
#define NMEA_ZDA_MES_POS	3
#define NMEA_ZDA_ANIO_POS	4
#define NMEA_ZDA_HHUTC_POS	5
#define NMEA_ZDA_MMUTC_POS	6



status_t proc_zda(nmea_t* nmea, char* cadena){
	
	char* cad_arr[NMEA_DELIM_CANT_MAX];
	size_t cant;
	status_t st;
	
	if ( !cadena || !nmea )
		return ST_ERR_PUNT_NULL;
	
	if ( split_delim( cadena , cad_arr , NMEA_DELIM_CHAR ) < NMEA_DELIM_CANT_MIN )
		return ST_ERR_ZDA_INVALIDA;

	if ( ( st = str2hora( cad_arr[NMEA_ZDA_HORA_POS] , &nmea->zda.hora ) ) != ST_OK )
		return ST_ERR_ZDA_INVALIDA;
		/* FALTA TERMINAR */
	
}
