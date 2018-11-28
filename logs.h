#include <stdio.h>

/* error */
#define MSJ_ERR_OPEN_FILE "No se pudo abrir el archivo"
#define MSJ_ERR_INV_CHKSUM "El checksum no concuerda"
#define MSJ_ERR_INV_LONG_UBX "El mensaje UBX tiene un largo inválido"
#define MSJ_ERR_INV_NMEA "El mensaje NMEA está mal formado"

/* warning */
#define MSJ_WARN_ID_DESC "No se reconoce el ID"
#define MSJ_WARN_FIX_INV "Fix inválido"
#define MSJ_WARN_FULL_LIST "La lista esta llena. Se descarta el mensaje más viejo"

/* debug */
#define MSJ_DB_BYTES_SYNC "Buscando bytes de sincronismo"
#define MSJ_DB_ID_DETECT "ID identificado: " //para poner despues que ID
#define MSJ_DB_MSJ_DET "Se recolectó un mensaje"
#define MSJ_DB_MSJ_UP "Se cargó un mensaje en la lista"

/* defino el tipo log_t */
typedef enum log_t {
    ERR_OPEN_FILE, ERR_INV_CHKSUM, ERR_INV_LONG_UBX,
    ERR_INV_NMEA, WARN_ID_DESC, WARN_FIX_INV, WARN_FULL_LIST,
    DB_BYTES_SYNC, DB_ID_DETECT, DB_MSJ_DET, DB_MSJ_UP
} log_t;
