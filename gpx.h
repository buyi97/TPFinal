#ifndef GPX__H
#define GPX__H

/*Estructura para GPX, con los datos a guardar*/
typedef struct gpx{
	struct metadata_t{
		char nombre[MAX_NOMBRE+1];
		fecha_t fecha;
		hora_t hora;
	}metadata_t;
	fecha_t fecha;
	hora_t hora;
	double latitud;
	double longitud;
	float elevacion;
}gpx_t;

#endif