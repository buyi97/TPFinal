#ifndef UBX__H
#define UBX__H
#include "fecha.h"

#define BUFFER_LEN      120 /*tamaño del buffer. El tamaño del buffer debe ser mayor a la máxima longitud posible para una sentencia UBX*/

 
#define SYNC_CHAR1 	    		0xB5
#define SYNC_CHAR2 		    	0X62
#define MASK_SIGNO 	    		0x80000000
#define SHIFT_SIGNO		    	31
#define MASK_EXPONENTE  		0x7f800000
#define SHIFT_EXPONENTE	  	23
#define MASK_MANTISA 	    	0x007fffff
#define MASK_BIT_IMPLICITO	0x80000000
#define SHIFT_BYTE 			    8
#define LEN_LARGO 		    	2 
#define POS_PAYLOAD 	    	4 
#define POS_LARGO 		    	2

typedef unsigned char uchar; 
typedef unsigned long ulong; 

status_t readline_ubx(uchar ** sentencia, bool * eof, FILE * fin);
bool get_sentence(uchar * buffer, bool * eof, FILE * fin);
void load_buffer(uchar * buffer, size_t pos, bool * eof, FILE * fin);
void fread_grind(void *ptr, size_t size, size_t nmemb, FILE *stream, bool * eof);
bool checksum(const uchar *buffer);
ulong letol(const uchar * string, size_t pos, size_t len);
double lotof(ulong entero);
#endif
