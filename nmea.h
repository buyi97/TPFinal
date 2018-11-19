#ifndef NMEA__H
#define NMEA__H

#include "nmea.c"

#define NMEA_DELIM_CHAR ','

#define NMEA_ID_LEN 3

#define NMEA_CANT_TIPOS	3

#define NMEA_GGA_STR "GGA"
#define NMEA_RMC_STR "RMC"
#define NMEA_ZDA_STR "ZDA"

/*Tipo de dato para la CALIDAD DEL FIX*/
typedef enum calidad_t{ 
	CAL_INVALIDO, 
	CAL_FIX_GPS, 
	CAL_FIX_DGPS, 
	CAL_FIX_PPS, 
	CAL_RTK, 
	CAL_RTK_FLOAT, 
	CAL_DEAD_RECK, 
	CAL_MANUAL, 
	CAL_SIMULATION 
}calidad_t;

/*Estructura para GGA, con los datos a guardar*/
typedef struct gga{
	struct hora_t hora;
	double latitud;
	double longitud;
	calidad_t calidad;
	unsigned int cant_satelites;
	float hdop;
	float elevacion;
	float sep_geoide;
}gga_t;

/*Estructura para ZDA, con los datos a guardar*/
typedef struct zda{
	struct fecha_t fecha;
	struct hora_t hora;
	int hh_utc;
	int mm_utc;
}zda_t;

/*Estructura para RMC, con los datos a guardar*/
typedef struct rmc{
	struct fecha_t fecha;
	struct hora_t hora;
	bool status;
	double latitud;
	double longitud;
	double velocidad;
	float ang_seg;
	float desv_mag;
}rmc_t;

/*Tipo para el id de las sentencia NMEA*/
typedef enum nmea_id{
	RMC,
	ZDA,
	GGA,
}nmea_id

/*Estructura NMEA, con los datos a guardar (contiene una union de rmc_t, zda_t, y gga_t porque pueden venir cualquiera de los 3)*/
typedef struct nmea{
	nmea_id	id;
	union sentencia {
   		rmc_t rmc;
   		zda_t zda;
   		gga_t gga;
	}sentencia;  
}nmea_t

/*Prototipos*/
status_t get_nmea_id ( const char *cadena , nmea_id* id );
status_t proc_zda(nmea_t* nmea, char* cadena);
status_t proc_zda(nmea_t* nmea, char* cadena);
status_t proc_zda(nmea_t* nmea, char* cadena);
status_t proc_nmea( char* cadena );
bool verify_checksum ( char* str_origen );

#endif
