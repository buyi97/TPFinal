/*Acá vamos a poner las estructuras y tipos enumerativos que vamos a usar, después las ordenamos bien, por ahora va esto*/

typedef enum protocol{
		P_NMEA,
		P_UBX,
}protocol_t;

typedef struct config{
		bool help;
		char nombre[MAX_NOMBRE+1];
		protocol_t protocol;
		char fin[MAX_NOMBRE+1];
		char fout[MAX_NOMBRE+1];
		char flog[MAX_NOMBRE+1];
}config_t;
