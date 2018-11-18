/**
* @file proc_gga.c
* @Author buyi97
* @date 17/11/2019
* @brief Procesar una cadena GGA (del protocolo NMEA)
*/

#include "nmea.h"
#include <string.h>
#include "fecha.h"
#include "geopos.h"
/**
* @brief Cargar en una estructura los datos de GGA a partir de una cadena.
* @param Cadena GGA, estructura nmea;
* @return El estado en el que terminó la función (si fue todo bien ST_OK)
*/

#define NMEA_GGA_HORA_POS	1
#define NMEA_GGA_LAT_POS	2
#define NMEA_GGA_LON_POS	4
#define NMEA_GGA_CAL_POS	6
#define NMEA_GGA_SAT_POS	7
#define NMEA_GGA_HDOP_POS	8
#define NMEA_GGA_ELE_POS	9
#define NMEA_GGA_SEP_POS	11

#define MAX_CALIDAD	8
#define MAX_SATELITES 12

/*Se asume que el checksum fue verificado*/

status_t proc_zda(nmea_t* nmea, char* cadena){
	
	char* cad_arr[NMEA_DELIM_CANT_MAX];
	size_t cant;
	status_t st;
	char* ctemp;
	
	if ( !cadena || !nmea )
		return ST_ERR_PUNT_NULL;
	
	if ( split_delim( cadena , cad_arr , NMEA_DELIM_CHAR ) < NMEA_DELIM_CANT_MIN )
		return ST_ERR_SENTENCIA_INVALIDA;

	if ( ( st = str2hora( cad_arr[NMEA_GGA_HORA_POS] , &nmea->gga.hora ) ) != ST_OK )
		return st;
	
	if ( ( st = str2lat( cad_arr[NMEA_GGA_LAT_POS], cad_arr[NMEA_GGA_LAT_POS + 1] , &nmea->gga.latitud ) ) != ST_OK )
		return st;
		
	if ( ( st = str2lon( cad_arr[NMEA_GGA_LON_POS], cad_arr[NMEA_GGA_LON_POS + 1] , &nmea->gga.longitud ) ) != ST_OK )
		return st;
	
	nmea->gga.calidad = strtoul( cad_arr[NMEA_GGA_CAL_POS] , &ctemp, 10 );

	if ( *ctemp != '\0' )
		return ST_ERR_FIX_INVALIDO;

	if ( nmea->gga.calidad < 1  || nmea->gga.calidad > MAX_CALIDAD )
		return ST_ERR_FIX_INVALIDO;
	
	nmea->gga.cant_sat = strtoul( cad_arr[NMEA_GGA_SAT_POS] , &ctemp, 10 );

	if ( *ctemp != '\0' )
		return ST_ERR_FIX_INVALIDO;

	if ( nmea->gga.cant_sat < 0  || nmea->gga.cant_sat > MAX_SATELITES )
		return ST_ERR_FIX_INVALIDO;
	
	nmea->gga.hdop = strtod( cad_arr[NMEA_GGA_HDOP_POS] , &ctemp );
	
	if ( *ctemp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	nmea->gga.elevacion = strtod( cad_arr[NMEA_GGA_ELE_POS] , &ctemp );
	
	if ( *ctemp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	nmea->gga.sep_geoide = strtod( cad_arr[NMEA_GGA_SEP_POS] , &ctemp );
	
	if ( *ctemp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	return ST_OK;	
	
}
