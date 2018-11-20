#include <stdio.h>
#include "nmea.h"
#include "estructuras.h"
//definicion de los chars a usar
#define CHAR_START 		"<"
#define CHAR_END 		">"
#define CHAR_QUESTION 	"?"
#define CHAR_COMILLAS 	"\""
#define CHAR_EQUAL 		"="
#define CHAR_BAR 		"/"
#define CHAR_FECHA_SEP	"-"
#define CHAR_HORA_SEP	":"
#define CHAR_FECHA_END	"T"
#define CHAR_HORA_END 	"Z"

//definicion de las cadenas a usar
#define MSJ_XML 			"xml"
#define MSJ_VERSION 		"version"
#define MSJ_ENCODING		"encoding"
#define MSJ_GPX 			"gpx"
#define MSJ_VERSION 		"version"
#define MSJ_CREATOR 		"creator"
#define MSJ_XMLNS 			"xmlns"
#define MSJ_METADATA 		"metadata"
#define MSJ_NAME 			"name"
#define MSJ_TIME			"time"
#define MSJ_TRK 			"trk"
#define MSJ_TRKSEG 			"trkseg"
#define MSJ_TRKPT 			"trkpt"
#define MSJ_LAT 			"lat"
#define MSJ_LON 			"lon"
#define MSJ_ELE 			"ele"

//definicion de las constantes
#define VERSION_XML	"1.0"
#define VERSION_GPX	"1.1"
#define ENCODING 	"UTF -8"
#define CREATOR 	"95.11 TP1 - Grupo LPL"
#define XMLNS		"http://www.topografix.com/GPX/1/1"

//prototipos de todas las funciones contenidas
void print_encabezado(void);
void print_metadata(struct fix_t * fix);
void print_trk_start(void);
void print_trkpt(struct fix_t* fix);
void print_trk_end(void);
void print_acabado(void);
//fin de prototipos

//comienzo del codigo de las funciones
void print_encabezado(FILE * fout){
	//imprimir primer linea
	fprintf(fout, "%s%s %s %s %s%s%s%s %s%s%s%s%s%s\n\n",
	CHAR_START, CHAR_QUESTION,
	MSJ_XML,
	MSJ_VERSION, CHAR_EQUAL, CHAR_COMILLAS,VERSION_XML,CHAR_COMILLAS,
	MSJ_ENCODING,CHAR_EQUAL,CHAR_COMILLAS,ENCODING,CHAR_COMILLAS
	CHAR_QUESTION, CHAR_END
	);
	//imprimir la segunda linea
	fprintf(fout, "%s%s %s %s%s%s%s %s %s%s%s%s %s %s%s%s%s%s\n",
	CHAR_START,
	MSJ_GPX,
	MSJ_VERSION,CHAR_EQUAL,CHAR_COMILLAS,VERSION_GPX,CHAR_COMILLAS,
	MSJ_CREATOR,CHAR_EQUAL,CHAR_COMILLAS,CREATOR,CHAR_COMILLAS,
	MSJ_XMLNS, CHAR_EQUAL,CHAR_COMILLAS,XMLNS,CHAR_COMILLAS,
	CHAR_END);

}

void print_metadata(struct fix_t * fix, FILE * fout){

	fprintf(fout, "\t%s%s%s\n",
	CHAR_START,	MSJ_METADATA, CHAR_END);	//imprime la primer linea de metadata

	fprintf(fout, "\t\t%s%s%s%s%s%s%s%s\n",
	CHAR_START,MSJ_NAME, CHAR_END,
	fix->nombre,
	CHAR_START,CHAR_BAR,MSJ_NAME, CHAR_END);	//imprime el nombre del archivo

	fprintf(fout, "\t\t%s%s%s%d%s%02d%s%02d%s%02d%s%02d%s%02d%s%s%s%s%s\n",
	CHAR_START,MSJ_TIME, CHAR_END,
	fix->fecha.year,CHAR_FECHA_SEP,fix->fecha.month,CHAR_FECHA_SEP,fix->fecha.day,CHAR_FECHA_END, 	//imprime la fecha
	fix->hora.hh,CHAR_HORA_SEP,fix->hora.mm,CHAR_HORA_SEP,(int)fix->hora.ss,CHAR_HORA_END, 				//imprime la hora
	CHAR_START,CHAR_BAR,MSJ_TIME, CHAR_END);	//imprime la fecha y hora

	fprintf(fout, "\t%s%s%s%s\n",
	CHAR_START,	CHAR_BAR, MSJ_METADATA, CHAR_END);	//imprime la primer ultima de metadata

}


void print_trk_start(FILE * fout){

	fprintf(fout, "\t%s%s%s\n",
	CHAR_START,	MSJ_TRK, CHAR_END);	//imprime la primer linea de trk

	fprintf(fout, "\t\t%s%s%s\n",
	CHAR_START,	MSJ_TRKSEG, CHAR_END);	//imprime la primer linea de trkseg

	//ejemplo <trk>
	//			<trkseg>
}

void print_trkpt(struct fix_t* fix, FILE * fout){

	fprintf(fout, "\t\t\t%s%s %s%s%s%lf%s %s%s%s%lf%s%s\n",
	CHAR_START, MSJ_TRKPT,
	MSJ_LAT, CHAR_EQUAL, CHAR_COMILLAS,fix->latitud,CHAR_COMILLAS,
	MSJ_LON, CHAR_EQUAL, CHAR_COMILLAS,fix->longitud,CHAR_COMILLAS,
	CHAR_END);	//imprime la primer linea de trkpt	ejemplo: <trkpt lat="19.918633" lon="-77.709016">

	fprintf(fout, "\t\t\t\t%s%s%s%lf%s%s%s%s\n",
	CHAR_START,MSJ_ELE, CHAR_END,
	fix->elevacion,
	CHAR_START,CHAR_BAR,MSJ_ELE, CHAR_END); //imprime la elevacion ejemplo: <ele>0.000000</ele>

	fprintf(fout, "\t\t\t\t%s%s%s%d%s%02d%s%02d%s%02d%s%02d%s%06.03lf%s%s%s%s%s\n",
	CHAR_START,MSJ_TIME, CHAR_END,
	fix->fecha.year,CHAR_FECHA_SEP,fix->fecha.month,CHAR_FECHA_SEP,fix->fecha.day,CHAR_FECHA_END, 	//imprime la fecha
	fix->hora.hh,CHAR_HORA_SEP,fix->hora.mm,CHAR_HORA_SEP,fix->hora.ss,CHAR_HORA_END, 				//imprime la hora
	CHAR_START,CHAR_BAR,MSJ_TIME, CHAR_END);	//imprime la fecha y hora ejemplo: <time>2018-09-30T11:28:36.854Z</time>

	fprintf(fout, "\t\t\t%s%s%s%s\n",
	CHAR_START,CHAR_BAR,MSJ_TRKPT,CHAR_END); //imprime la ultima linea de trkpt ejemplo: </trkpt>

	//la funcion imprime los datos de un fix

}

void print_trk_end(FILE * fout){

	fprintf(fout, "\t\t%s%s%s%s\n",
	CHAR_START,CHAR_BAR, MSJ_TRKSEG, CHAR_END);	//imprime la ultima linea de trkseg

	fprintf(fout, "\t%s%s%s%s\n",
	CHAR_START, CHAR_BAR, MSJ_TRK, CHAR_END);	//imprime la ultima linea de trk


	//ejemplo 	</trkseg>
	//		</trk>
}

void print_acabado (FILE * fout){

	fprintf(fout, "%s%s%s%s\n",
	CHAR_START,CHAR_BAR, MSJ_GPX, CHAR_END);	//imprime la ultima linea de gpx ejemplo </gpx>

}
