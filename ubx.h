#ifndef UBX__H
#define UBX__H
#include "fecha.h"

/*tamaño del buffer*/
#define BUFFER_LEN 120 /*La longitúd del buffer debe ser mayor a la máxima longitud posible para una sentencia UBX*/

#define SYNC_CHAR1 			0xB5
#define SYNC_CHAR2 			0X62
#define LOTOF_MASK_SIGNO	0x80000000
#define SHIFT_SIGNO			31
#define SLETOL_MASK_SIGNO	0X80
#define MASK_EXPONENTE 		0x7f800000
#define SHIFT_EXPONENTE		23
#define MASK_MANTISA 		0x007fffff
#define MASK_BIT_IMPLICITO	0x80000000
#define SHIFT_BYTE 			8
#define LEN_LARGO 			2 
#define POS_PAYLOAD 		4 
#define POS_LARGO 			2

/*macros para procesar el payload PVT*/
#define UBX_PVT_GNS_FIX_OK_MASK	1
#define UBX_PVT_GNS_FIX_OK_POS	21
#define UBX_PVT_GNS_FIX_OK_SHIFT 0
#define UBX_PVT_ELEVACION_POS	32
#define UBX_PVT_ELEVACION_LEN	4
#define UBX_PVT_LATITUD_POS 	28
#define UBX_PVT_LATITUD_LEN 	4
#define UBX_PVT_LONGITUD_POS 	24
#define UBX_PVT_LONGITUD_LEN 	4
#define UBX_PVT_YEAR_POS 		4
#define UBX_PVT_YEAR_LEN 		2
#define UBX_PVT_MONTH_POS 		6
#define UBX_PVT_DAY_POS 		7
#define UBX_PVT_HH_POS 			8
#define UBX_PVT_MM_POS 			9
#define UBX_PVT_SS_POS 			10


/*macros para procesar el payload TIM_TOS*/
#define UBX_TIM_TOS_YEAR_POS 	8
#define UBX_TIM_TOS_YEAR_LEN	2
#define UBX_TIM_TOS_MONTH_POS	10
#define UBX_TIM_TOS_DAY_POS		11
#define UBX_TIM_TOS_HH_POS		12
#define UBX_TIM_TOS_MM_POS		13
#define UBX_TIM_TOS_SS_POS		14

/*macros para procesar el payload NAV_POSLLH*/
#define UBX_NAV_POSLLH_ELEVACION_POS 	12
#define UBX_NAV_POSLLH_ELEVACION_LEN 	4
#define UBX_NAV_POSLLH_LATITUD_POS		8
#define UBX_NAV_POSLLH_LATITUD_LEN		4
#define UBX_NAV_POSLLH_LONGITUD_POS 	4
#define UBX_NAV_POSLLH_LONGITUD_LEN 	4


typedef unsigned char uchar; 
typedef unsigned long ulong; 

/*Tipo para el id de las sentencia UBX*/
typedef enum ubx_id{
	NAV_PVT,
	TIM_TOS,
	NAV_POSLLH,
}ubx_id;

/*Estructura para nav_pvt, con los datos a guardar*/
typedef struct nav_pvt{
	bool gns_fix_ok;
	fecha_t fecha;
	hora_t hora;
	double latitud;
	double longitud;
	double elevacion;
}nav_pvt_t;

/*Estructura para tim_tos, con los datos a guardar*/
typedef struct tim_tos{
	fecha_t fecha;
	hora_t hora;
}tim_tos_t;

/*Estructura para nav_posllh, con los datos a guardar*/
typedef struct nav_posllh{
	double latitud;
	double longitud;
	double elevacion;
}nav_posllh_t;

typedef struct ubx{
	ubx_id	id;
	union type {
   		nav_pvt_t pvt;
   		nav_posllh_t posllh;
   		tim_tos_t tim_tos;
	}type;  
}ubx_t;

status_t proc_nav_posllh(const char * payload, ubx_t * pvt);
status_t proc_tim_tos(const char * payload, ubx_t * pvt);
status_t proc_nav_pvt(const char * payload, ubx_t * pvt);
status_t readline_ubx(uchar ** sentencia, bool * eof, FILE * fin);
bool get_sentence(uchar * buffer, bool * eof, FILE * fin);
void load_buffer(uchar * buffer, size_t pos, bool * eof, FILE * fin);
void fread_grind(void *ptr, size_t size, size_t nmemb, FILE *stream, bool * eof);
bool checksum(const uchar *buffer);
ulong letol(const uchar * string, size_t pos, size_t len);
double lotof(ulong entero);
long sletol(const uchar *string, size_t pos, size_t len);

#endif
