#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "status.h"
#include "estructuras.h"

#define BUFFER_LEN 400 /*La longitúd del buffer debe ser mayor a la máxima longitud posible para una sentencia UBX*/
#define SHIFT_BYTE 8
#define SIZE_OF_SYNC_CHARS 2
#define LARGO_LEN 2 
#define POS_PAYLOAD 4

typedef unsigned char uchar; 

bool checksum(const uchar *buffer);

int main (void){
	int i,
		j,
		ok=0,
		fail=0;
	FILE * fout;
	uchar ck_a = 0,
	      ck_b = 0,
	      sentence[100];

	srand(92);
	fout = fopen("UBXtest.txt", "wb");

	/*primeros caracteres de sentencia PVT*/
	sentence[0] = 0xB5;      
	sentence[1] = 0X62;
	sentence[2] = 0x01; 
	sentence[3] = 0x07;
	sentence[4] = 0x5C; /*largo igual a 92, sentencia PVT*/
	sentence[5] = 0x00;
	
	for(j = 0 ; j < 2000 ; j++){
		/*carga el payload*/
		for(i = 6 ; i < 98 ; i++){
			sentence[i] = rand()%255;
		}

		/*Calcula el checksum*/
		for(i = 2 ; i < 98 ; i++){
			ck_a = ck_a + sentence[i];
			ck_b = ck_b + ck_a;
		}

		sentence[98]=ck_a;
		sentence[99]=ck_b;
		ck_a = 0;
		ck_b = 0;

		fwrite(sentence,1,100,fout);
		
		if(checksum(sentence + 2))
			ok++;
		else 
			fail++;
		
	}

	printf("checksum OK: %d \nchecksum fail: %d\n", ok, fail);


	fclose(fout);

	return EXIT_SUCCESS;
}

/*calcula el checksum*/
bool checksum(const uchar *buffer){
	uchar ck_a = 0,
	      ck_b = 0;
	size_t largo = 0;
	int i;
	
	/*pasa el largo del payload de little-endian a size_t*/
	for(i = 0 ; i < LARGO_LEN ; i++){
		largo <<= SHIFT_BYTE;
		largo |= buffer[POS_PAYLOAD - 1 - i];
	}

	/*si el largo leído es mayor a la máxima longitud de una sentencia UBX hay un error en la sentencia*/
	if(largo > BUFFER_LEN)
		/*IMPRIMIR LOG*/
		return false;

	/*Calcula el checksum*/
	for(i = 0 ; i < (POS_PAYLOAD + largo) ; i++){
		ck_a = ck_a + buffer[i];
		ck_b = ck_b + ck_a;
	}

	/*compara el checksum calculado*/
	if (ck_a == buffer[i++] && ck_b == buffer[i]) /*al finalizar el 'for' anterior la posición 'i' corresponde al primer caracter de sincronismo*/
		return true;
	else
		return false;
}
