
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
typedef enum status_t{
    ST_OK, ST_ERR_DATO_INCOMP, ST_ERR_PUNT_NULL, ST_ERR_FECHA_INVALIDA,
    ST_ERR_MISSING_ARG, ST_ERR_MISSING_NAME,
    ST_ERR_OPEN_FILE, ST_ERR_INV_CHKSUM, ST_ERR_INV_LONG_UBX
    ST_ERR_INV_NMEA, ST_WARN_ID_DESC, ST_WARN_FIX_INV, ST_WARN_FULL_LIST,
    ST_DB_BYTES_SYNC, ST_DB_ID_DETECT, ST_DB_MSJ_DET, ST_DB_MSJ_UP}status_t;

void print_logs(status_t nivel_log ) {
    status_t logs;

    switch(logs) {

        case 'ST_ERR_OPEN_FILE':
            fprintf(stdout, MSJ_ERR_OPEN_FILE);
            break;
        case 'ST_ERR_INV_CHKSUM':
            fprint(stdout, MSJ_ERR_INV_CHKSUM);
            break;

    }
}

int main (void) {
    status_t logs = ST_ERR_INV_CHKSUM;

    print_logs(logs);

}
