/*Acá vamos a poner las estructuras y tipos enumerativos que vamos a usar, después las ordenamos bien, por ahora va esto*/

/*Tipo de dato para PROTOCOLO*/
typedef enum protocol{
	P_NMEA,
	P_UBX,
}protocol_t;

/*Estructura que le vamos a pasar a proc_argv, con las configuraciones del programa*/
typedef struct config{
	bool help;
	char nombre[MAX_NOMBRE+1];
	protocol_t protocol;
	char fin[MAX_NOMBRE+1];
	char fout[MAX_NOMBRE+1];
	char flog[MAX_NOMBRE+1];
}config_t;

/*Estructura de FECHA, año, mes y día con el calendario gregoriano*/
typedef struct fecha{	
	int year;	/* //estructura para la fecha */
	int month;
	int day;
}fecha_t;

/*Estructura de HORA, hora, minutos y segundos*/
typedef struct hora{	
	int hh;		/* //estructura para la hora */
	int mm;
	double ss;
}hora_t;

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

typedef struct zda{
	struct fecha_t fecha;
	struct hora_t hora;
	int hh_utc;
	int mm_utc;
}zda_t;

typedef struct rmc{
	struct hora_t hora;
	double latitud;
	double longitud;
	calidad_t calidad;
	unsigned int cant_satelites;
	float hdop;
	float elevacion;
	float sep_geoide;
}rmc_t;


