#ifndef FECHA__H
#define FECHA__H

#include "fecha.c"

typedef struct fecha_t{	int year;	/* estructura para la fecha */
			int month;
			int day;
			}fecha_t;

typedef struct hora_t{	int hh;		/* estructura para la hora */
			int mm;
			double ss;
			}hora_t;
      
status_t str2hora(char* cadena, struct hora_t* hora);
