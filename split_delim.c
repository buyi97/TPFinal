/**
* @file split_delim.c
* @Author buyi97
* @date 17/11/2019
* @brief Separar una cadena en varias a partir de un caracter delimitador
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* @brief Separar una cadena
* @param Cadena a cortar, arreglo de cadenas, char delimitador
* @return La cantidad de delimitadores encontrados
*/

size_t split_delim (char * cadena, char ** ptr2ptrarray, char delim) {
	
	size_t i=0;	/* variable de iteracion */

	if ( !cadena || !ptr2ptrarray )	/* valido los punteros */
		return 0;
	
	ptr2ptrarray[0] = cadena;
	
	if ( !( ptr2ptrarray[1] = strchr(cadena,delim) ) )	/* busco el primer delim */
		return 0;
	
	*(ptr2ptrarray[1])='\0';	/* le asigno un \0 */
	ptr2ptrarray[1]++;			/* le hago apuntar a un lugar despues del \0 */
	
	for (i = 2; ( ptr2ptrarray[i] = strchr(ptr2ptrarray[i-1],delim) ) ; i++) {
		
		ptr2ptrarray[i][0] = '\0';
		ptr2ptrarray[i]++;
		
	}

	return i;
	
}
