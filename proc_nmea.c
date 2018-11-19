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
* @brief Procesa una sentencia NMEA, creando por memoria dinámica la nmea_t
* @param Cadena NMEA (const), puntero doble a nmea_t
* @return El estado en el que terminó (ST_OK si todo fue bien)
*/


status_t proc_nmea( char* cadena , nmea_t ** nmea ){
	
	status_t st;
	status_t (*pfunc[ NMEA_CANT_TIPOS ])( nmea_t* , char* ) = { proc_rmc,  proc_zda,  proc_gga }; /*Puntero a funciones*/
	
	if ( !cadena || !nmea )
		return ST_ERR_PUNT_NULL;
	
	if ( verify_checksum( cadena ) == false )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	if (  !( *nmea = (nmea_t*)calloc(1,sizeof(nmea_t)) )
	    	return ST_ERR_NOMEM;
	
	if ( ( st = get_nmea_id( cadena , &((*nmea)->id) ) ) != ST_OK ){
		free(*nmea);
		*nmea=NULL;
		return st;
	}
	
	if ( ( st = (*pfunc[ (*nmea)->id) ])( *nmea , cadena ) ) != ST_OK ){
		free(*nmea);
		*nmea=NULL;
		return st;
	}
	
	return ST_OK;
	
}
