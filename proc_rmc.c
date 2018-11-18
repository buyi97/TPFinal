/**
* @file proc_rmc.c
* @Author buyi97
* @date 17/11/2019
* @brief Procesar una cadena RMC (del protocolo NMEA)
*/

#include "nmea.h"

/**
* @brief Cargar en una estructura los datos de RMC a partir de una cadena.
* @param Cadena RMC, estructura nmea;
* @return El estado en el que terminé la función (si fue todo bien ST_OK)
*/

#define NMEA_RMC_HORA_POS	1
#define NMEA_RMC_ST_POS	    2
#define NMEA_RMC_LAT_POS	3
#define NMEA_RMC_LON_POS	5
#define NMEA_RMC_VEL_POS	7
#define NMEA_RMC_ANG_POS	8
#define NMEA_RMC_FECHA_POS	9
#define NMEA_RMC_DESV_POS	10

#define STR_RMC_ACTIVE "A"
#define STR_RMC_VOID "V"

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

	if ( ( st = str2hora( cad_arr[NMEA_RMC_HORA_POS] , &nmea->rmc.hora ) ) != ST_OK )
		return st;
    
	if ( strcmp( cad_arr[NMEA_RMC_ST_POS] , STR_RMC_ACTIVE ) == 0 )
		nmea->rmc.status = true;
	else 
		return ST_ERR_SENTENCIA_INVALIDA;
	
	if ( ( st = str2lat( cad_arr[NMEA_RMC_LAT_POS], cad_arr[NMEA_RMC_LAT_POS + 1] , &nmea->rmc.latitud ) ) != ST_OK )
		return st;
		
	if ( ( st = str2lon( cad_arr[NMEA_RMC_LON_POS], cad_arr[NMEA_RMC_LON_POS + 1] , &nmea->rmc.longitud ) ) != ST_OK )
		return st;
	
	nmea->rmc.velocidad = strtod( cad_arr[NMEA_RMC_VEL_POS] , &ctemp );
	
	if ( *ctemp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	nmea->rmc.ang_seg = strtod( cad_arr[NMEA_RMC_ANG_POS] , &ctemp );
	
	if ( *ctemp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	if ( ( st = str2fecha( cad_arr[NMEA_RMC_FECHA_POS] , &nmea->rmc.fecha ) ) != ST_OK )
		return st;
	
	nmea->rmc.desv_mag = strtod( cad_arr[NMEA_RMC_DESV_POS] , &ctemp );
	
	if ( *ctemp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	return ST_OK;	
	
}
