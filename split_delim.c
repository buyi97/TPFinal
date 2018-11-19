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

	ptr2ptrarray[i] = cadena;
	i++;

	if ( !( ptr2ptrarray[i] = strchr(cadena,delim) ) )	/* busco el primer delim */
		return 0;

	ptr2ptrarray[i][0] = '\0';	/* le asigno un \0 */
	ptr2ptrarray[i]++;			/* le hago apuntar a un lugar despues del \0 */
	i++;
	
	for (; ( ptr2ptrarray[i] = strchr(ptr2ptrarray[i-1],delim) ) ; i++) {

		ptr2ptrarray[i][0] = '\0';
		ptr2ptrarray[i]++;

	}
	return i;

}
