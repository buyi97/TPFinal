#include <stdbool.h>

typedef enum protocol{
		NMEA,
		UBX,
}protocol_t;

typedef struct config{
		bool help;
		char nombre[MAX_NOMBRE+1];
		protocol_t protocol;
		FILE* fin;
		FILE* fout;
		FILE* flog;
}config_t;

#define CHAR_ARG_LCMD_START	'-'

#define STR_HELP_S "-h"
#define STR_HELP_L "--help"
#define STR_NAME_S "-n"
#define STR_NAME_L "--name"
#define STR_PROTOCOL_S "-p"
#define STR_PROTOCOL_L "--protocol"
#define STR_INFILE_S "-i"
#define STR_INFILE_L "--infile"
#define STR_OUTFILE_S "-o"
#define STR_OUTFILE_L "--outfile"
#define STR_LOGFILE_S "-l"
#define STR_LOGFILE_L "--logfile"

/* La funcion proc_argv recibe los argumentos en linea de comandos, y devuelve por interfaz una estructura con los datos que nos pasan */
status_t  proc_argv(int argc, char* argv[],config_t* config){
	
	char* ptemp; //puntero a char auxiliar
	status_t st; //guardo la informacion del estado

	for(i=1;i<argc;i++){
		if ( *(argv[i]) == CHAR_ARG_LCMD_START ){
			if( (strcmp(argv[i],STR_HELP_S)==0) || (strcmp(argv[i],STR_HELP_L)==0)){
				config->help = true;
				return ST_OK;
			}
			else if( (strcmp(argv[i],STR_NAME_S)==0 ) || (strcmp(argv[i],STR_NAME_L)==0) ){
				if ( (i+1) < argc ){
					strncpy(config->nombre,argv[i+1],MAX_NOMBRE);
				}
				else st = ST_ERR_MISSING_ARG;
			}
