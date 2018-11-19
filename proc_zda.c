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

/* todos los macros que se definan iran a un .h, no quedan aca*/
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
	long int ntemp
	char * temp;

	if ( !cadena || !nmea )
		return ST_ERR_PUNT_NULL;

    /* split devuelve la cant de cadenas que separo. Si ese numero es menor a
       NMEA_DELIM_CANT_MIN, se descarta el dato*/
	if ( split_delim( cadena , cad_arr , NMEA_DELIM_CHAR ) < NMEA_DELIM_CANT_MIN )
		return ST_ERR_SENTENCIA_INVALIDA;

	if ( ( st = str2hora( cad_arr[NMEA_ZDA_HORA_POS] , &nmea->zda.hora ) ) != ST_OK )
		return ST_ERR_SENTENCIA_INVALIDA;

    //if ( (st = str2fecha( cad_arr[NMEA_ZDA_HORA_POS] , &nmea->zda.fecha ) ) != ST_OK )
    //    return ST_ERR_SENTENCIA_INVALIDA;

	/* verifico que el dia sea un numero y si lo es lo cargo en la estructura */
	ntemp = strtol(cad_arr[NMEA_ZDA_DIA_POS], &temp, 10);
	if ( *temp != '\0' ) {
		return ST_ERR_SENTENCIA_INVALIDA;
	} else {
		ntemp = nmea->zda.fecha.day;
	}

	/* idem anterior para el mes */
	ntemp = strtol(cad_arr[NMEA_ZDA_MES_POS], &temp, 10);
	if ( *temp != '\0' ) {
		return ST_ERR_SENTENCIA_INVALIDA;
	} else {
		ntemp = nmea->zda.fecha.month;
	}

	/* idem anterior para el año */
	ntemp = strtol(cad_arr[NMEA_ZDA_ANIO_POS], &temp, 10);
	if ( *temp != '\0' ) {
		return ST_ERR_SENTENCIA_INVALIDA;
	} else {
		ntemp = nmea->zda.fecha.year;
	}

	/* verifico que zona horaria sea un numero y si lo es lo cargo en la estructura */
	ntemp = strtol(cad_arr[NMEA_ZDA_HHUTC_POS], &temp, 10);
	if ( *temp != '\0' ) {
		return ST_ERR_SENTENCIA_INVALIDA;
	} else {
		ntemp = nmea->zda.hh_utc;
	}

	/* idem anterior pero para los minutos de diferencia */
	ntemp = strtol(cad_arr[NMEA_ZDA_HHUTC_POS], &temp, 10);
	if ( *temp != '\0' ) {
		return ST_ERR_SENTENCIA_INVALIDA;
	} else {
		ntemp = nmea->zda.mm_utc;
	}

}
