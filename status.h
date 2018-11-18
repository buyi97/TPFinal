#ifndef STATUS__H
#define STATUS__H

#include "status.c"

typedef enum status_t{ 
			ST_OK, 
			ST_ERR_DATO_INCOMP, 
			ST_ERR_PUNT_NULL, 
			ST_ERR_FECHA_INVALIDA,
			ST_ERR_HORA_INVALIDA,
			ST_ERR_FIX_INVALIDO, 
			ST_ERR_MISSING_ARG, 
			ST_ERR_NO_NAME,
			ST_ERR_NO_PROTOCOL,
			ST_ERR_NO_INFILE,
			ST_ERR_NO_OUTFILE,
			ST_ERR_NO_LOGFILE
}status_t;

#endif
