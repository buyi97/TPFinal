/**
* @print_logs.c
* @Author pulpo
* @date 24/11/2018
* @brief La funcion recibe el log y un puntero a file e imprime
* el mensaje correspondiente en el archivo indicado.
*/

#include <stdio.h>

#define MSJ_ERR_OPEN_FILE "No se pudo abrir el archivo"
#define MSJ_ERR_INV_CHKSUM "El checksum no concuerda"
#define MSJ_ERR_INV_LONG_UBX "El mensaje UBX tiene un largo inválido"
#define MSJ_ERR_INV_NMEA "El mensaje NMEA está mal formado"

#define MSJ_WARN_ID_DESC "No se reconoce el ID"
#define MSJ_WARN_FIX_INV "Fix inválido"
#define MSJ_WARN_FULL_LIST "La lista esta llena. Se descarta el mensaje más viejo"

#define MSJ_DB_BYTES_SYNC "Buscando bytes de sincronismo"
#define MSJ_DB_ID_DETECT "ID identificado: " //para poner despues que ID
#define MSJ_DB_MSJ_DET "Se recolectó un mensaje"
#define MSJ_DB_MSJ_UP "Se cargó un mensaje en la lista"

//typedef enum {"error", "warn", "debug"} log_t;
void print_logs (status_t logs, FILE *flogs) {

    switch(logs) {

        /* Errores (ERR) */
        case ST_ERR_OPEN_FILE:
            fprintf(flogs, "%s\n", MSJ_ERR_OPEN_FILE);

        case ST_ERR_INV_CHKSUM:
            fprintf(flogs, "%s\n", MSJ_ERR_INV_CHKSUM);
            break;

        case ST_ERR_INV_LONG_UBX:
            fprintf(flogs, "%s\n", MSJ_ERR_INV_LONG_UBX);
            break;

        case ST_ERR_INV_NMEA:
            fprintf(flogs, "%s\n", MSJ_ERR_INV_NMEA);
            break;
        /* Warnings (WARN) */
        case ST_WARN_ID_DESC:
            fprintf(flogs, "%s\n", MSJ_WARN_ID_DESC);
            break;

        case ST_WARN_FIX_INV:
            fprintf(flogs, "%s\n", MSJ_WARN_FIX_INV);
            break;

        case ST_WARN_FULL_LIST:
            fprintf(flogs, "%s\n", MSJ_WARN_FULL_LIST);
            break;

        /* Debug (DB) */
        case ST_DB_BYTES_SYNC:
            fprintf(flogs, "%s\n", MSJ_DB_BYTES_SYNC);
            break;

        case ST_DB_ID_DETECT:
            fprintf(flogs, "%s\n", MSJ_DB_ID_DETECT);
            break;

        case ST_DB_MSJ_DET:
            fprintf(flogs, "%s\n", MSJ_DB_MSJ_DET);
            break;

        case ST_DB_MSJ_UP:
            fprintf(flogs, "%s\n", MSJ_DB_MSJ_UP);
            break;
    }
}
