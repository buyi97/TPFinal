/**
* @print_logs.c
* @Author pulpo
* @date 24/11/2018
* @brief La funcion recibe el log y un puntero a file e imprime
* el mensaje correspondiente en el archivo indicado.
*/

#include "logs.h"

void print_logs (log_t logs/*, FILE *stdout*/) {

    switch(logs) {

        /* Errores (ERR) */
        case ERR_OPEN_FILE:
            fprintf(stdout, "%s\n", MSJ_ERR_OPEN_FILE);

        case ERR_INV_CHKSUM:
            fprintf(stdout, "%s\n", MSJ_ERR_INV_CHKSUM);
            break;

        case ERR_INV_LONG_UBX:
            fprintf(stdout, "%s\n", MSJ_ERR_INV_LONG_UBX);
            break;

        case ERR_INV_NMEA:
            fprintf(stdout, "%s\n", MSJ_ERR_INV_NMEA);
            break;
        /* Warnings (WARN) */
        case WARN_ID_DESC:
            fprintf(stdout, "%s\n", MSJ_WARN_ID_DESC);
            break;

        case WARN_FIX_INV:
            fprintf(stdout, "%s\n", MSJ_WARN_FIX_INV);
            break;

        case WARN_FULL_LIST:
            fprintf(stdout, "%s\n", MSJ_WARN_FULL_LIST);
            break;

        /* Debug (DB) */
        case DB_BYTES_SYNC:
            fprintf(stdout, "%s\n", MSJ_DB_BYTES_SYNC);
            break;

        case DB_ID_DETECT:
            fprintf(stdout, "%s\n", MSJ_DB_ID_DETECT);
            break;

        case DB_MSJ_DET:
            fprintf(stdout, "%s\n", MSJ_DB_MSJ_DET);
            break;

        case DB_MSJ_UP:
            fprintf(stdout, "%s\n", MSJ_DB_MSJ_UP);
            break;
    }
}

int main (void) {
    log_t log_ = DB_MSJ_UP;
    print_logs(log_);

}

/*
CABLEVISION IAIA
20043845307
*/
