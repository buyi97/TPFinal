/**
* @file proc_nmea.c
* @Author buyi97
* @date 18/11/2019
* @brief Procesa una sentencia NMEA completa (tipo de sentencia)
*/

#include "nmea.h"
#include <string.h>
#include "status.h"


/**
* @brief Procesa una sentencia NMEA
* @param Cadena NMEA (const)
* @return El estado en el que terminó (ST_OK si todo fue bien)
*/


status_t proc_nmea( char* cadena ){
	
	nmea_t nmea;
	status_t st;
	status_t (*pfunc[ NMEA_CANT_TIPOS ])( nmea_t* , char* ) = { proc_rmc,  proc_zda,  proc_gga }; /*Puntero a funciones*/
	
	if ( !cadena )
		return ST_ERR_PUNT_NULL;
	
	if ( verify_checksum( cadena ) == false )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	if ( ( st = get_nmea_id( cadena , &nmea.id ) ) != ST_OK )
		return st;
	
	if ( ( st = (*pfunc[ nmea.id ])( &nmea , cadena ) ) != ST_OK )
		return st;
	
	/*FALTA TERMINAR LA FUNCION, Y TERMINAR DE CERRAR LA IDEA*/
	
}
