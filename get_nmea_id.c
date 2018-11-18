/**
* @file get_nmea_id.c
* @Author buyi97
* @date 17/11/2019
* @brief Obtiene el id del NMEA (tipo de sentencia)
*/

#include "nmea.h"
#include <string.h>
#include "status.h"

/**
* @brief Obtiene el id de la cadena NMEA
* @param Cadena NMEA (const)
* @return tipo de dato nmea_id (definido en "nmea.h") con el valor del tipo de sentencia de NMEA
*/

status_t get_nmea_id ( const char *cadena , nmea_id* id ) {

	char * ptr2delim;
	
	if ( !cadena || !id )
		return ST_ERR_PUNT_NULL;
	
	ptr2delim = strstr ( cadena, NMEA_DELIM_CHAR );
  
 /*  Se valida ptr2coma para el caso en que es nulo. */
	if ( !ptr2delim )
		return ST_ERR_SENTENCIA_INVALIDA;

	if ( strncmp ( ptr2delim-NMEA_ID_LEN) , NMEA_GGA_STR , NMEA_ID_LEN) == 0) {
		*id = GGA;
		return ST_OK;
	}
	if ( strncmp ( ptr2delim-NMEA_ID_LEN) , NMEA_RMC_STR , NMEA_ID_LEN) == 0) {
		*id = RMC;
		return ST_OK;
	}
	if ( strncmp ( ptr2delim-NMEA_ID_LEN) , NMEA_ZDA_STR , NMEA_ID_LEN) == 0) {
		*id = ZDA;
		return ST_OK;
	}
	
	return ST_ERR_ID_INVALIDO;

}
