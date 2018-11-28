/**
* @print_logs.c
* @Author pulpo
* @date 24/11/2018
* @brief La funcion recibe el log y un puntero a file e imprime
* el mensaje correspondiente en el archivo indicado.
*/

#include "logs.h"

void print_logs (log_t logs, FILE *flogs) {
    
    if (!flogs)
        return ST_ERR_PUNT_NULL;
    
    switch(logs) {

        /* Errores (ERR) */
        case ERR_OPEN_FILE:
            fprintf(flogs, "%s\n", MSJ_ERR_OPEN_FILE);

        case ERR_INV_CHKSUM:
            fprintf(flogs, "%s\n", MSJ_ERR_INV_CHKSUM);
            break;

        case ERR_INV_LONG_UBX:
            fprintf(flogs, "%s\n", MSJ_ERR_INV_LONG_UBX);
            break;

        case ERR_INV_NMEA:
            fprintf(flogs, "%s\n", MSJ_ERR_INV_NMEA);
            break;
        /* Warnings (WARN) */
        case WARN_ID_DESC:
            fprintf(flogs, "%s\n", MSJ_WARN_ID_DESC);
            break;

        case WARN_FIX_INV:
            fprintf(flogs, "%s\n", MSJ_WARN_FIX_INV);
            break;

        case WARN_FULL_LIST:
            fprintf(flogs, "%s\n", MSJ_WARN_FULL_LIST);
            break;

        /* Debug (DB) */
        case DB_BYTES_SYNC:
            fprintf(flogs, "%s\n", MSJ_DB_BYTES_SYNC);
            break;

        case DB_ID_DETECT:
            fprintf(flogs, "%s\n", MSJ_DB_ID_DETECT);
            break;

        case DB_MSJ_DET:
            fprintf(flogs, "%s\n", MSJ_DB_MSJ_DET);
            break;

        case DB_MSJ_UP:
            fprintf(flogs, "%s\n", MSJ_DB_MSJ_UP);
            break;
    }
}
