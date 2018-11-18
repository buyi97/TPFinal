/**
* @file nmea_chksum.c
* @Author buyi97
* @date 17/11/2019
* @brief Verificar el checksum de una cadena del protocolo NMEA
*/

#include "nmea.h"
#include <string.h>

#define TOKEN_CHKSUM '*'

/**
* @brief Calcular el checksum de una cadena
* @param Cadena
* @return Unsigned char con el valor del cheksum
*/

unsigned char checksum ( const char * sentence ){
	
  unsigned char sum = 0;
	
  if ( !sentence )
    return 0;
  
	while (* sentence )
	  sum ^= * sentence ++;
    
	return sum;
}

/**
* @brief Verificar el checksum de una cadena NMEA
* @param  NMEA
* @return Booleano, true si se cumple el checksum, false si no
*/

bool verify_checksum ( char* str_origen ){
	
	char* ptr2chksum;
	size_t i=0;
	char* temp;
	unsigned char char_temp;
	unsigned long int num_temp;

	ctemp = strchr(str_origen,TOKEN_CHKSUM);
	
	if (!ctemp)
		return false;
	
	*temp = '\0';
	ptr2chksum = temp + 1;
	
	char_temp = checksum( str_origen );
	num_temp = strtoul( (ptr2chksum) , &temp , 16);
	
	if ( *temp != '\0' && *temp != '\n'  && *temp != '\r' )  /*el '\r' para ser compatible con Windows (sistema usado para pruebas)*/
		return false;
	
	if (char_temp == num_temp)
		return true;

	return false;

}
