#include <stdbool.h>
#include <string.h>

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

#define STR_NMEA	"nmea"
#define STR_UBX		"ubx"

#define STR_STDIN	"-"
#define STR_STDOUT	"-"
#define STR_STDERR	"-"

/* La funcion proc_argv recibe los argumentos en linea de comandos, y devuelve por interfaz una estructura con los datos que nos pasan */
status_t  proc_argv(int argc, char* argv[],config_t* config){
	
	char* ptemp; //puntero a char auxiliar
	status_t st= ST_OK ; //guardo la informacion del estado
	bool boolprot=false;

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
				else {st = ST_ERR_NO_NAME;
				}
			}

			else if( (strcmp(argv[i],STR_PROTOCOL_S)==0) || (strcmp(argv[i],STR_PROTOCOL_L)==0) ){
				if ( (i+1) < argc){
					if ( strcmp(argv[i+1], STR_NMEA ) ) == 0 ){
						config->protocol = P_NMEA;
						boolprot=true;
					}
					else if ( strcmp(argv[i+1], STR_UBX ) ) == 0 ){
						config->protocol = P_NMEA;
						boolprot=true;
					}						
				}
				else {	st = ST_ERR_NO_PROTOCOL;
				}
			}
			else if( (strcmp(argv[i],STR_INFILE_S)==0) || (strcmp(argv[i],STR_INFILE_L)==0) ){
				if ( (i+1)<argc ){
					if ( strcmp(argv[i+1], STR_STDIN ) ) == 0 ){
						strcpy(config->fin,"stdin");
					}
					else{ strncpy( config->fin , argv[i+1] , MAX_NOMBRE );
					}	
				}
				else {	st = ST_ERR_NO_INFILE;
				}
			}

			else if( (strcmp(argv[i],STR_OUTFILE_S) ==0) || (strcmp(argv[i],STR_OUTFILE_S)==0) ){
				if ( (i+1)<argc ){
					if ( strcmp(argv[i+1], STR_STDOUT ) ) == 0 ){
						strcpy(config->fin,"stdout");
					}
					else{ strncpy( config->fout , argv[i+1] , MAX_NOMBRE );
					}	
				}
				else {	st = ST_ERR_NO_OUTFILE;
				}
			}
			else if( (strcmp(argv[i],STR_LOGFILE_S) ==0) || (strcmp(argv[i],STR_LOGFILE_S)==0) ){
				if ( (i+1)<argc ){
					if ( strcmp(argv[i+1], STR_STDERR ) ) == 0 ){
						strcpy(config->fin,"stderr");
					}
					else{ strncpy( config->flog , argv[i+1] , MAX_NOMBRE );
					}	
				}
				else {	st = ST_ERR_NO_LOGFILE;
				}
			}
		}
	}
	
	if ( boolprot == false )
		return ST_ERR_NO_PROTOCOL;
	
	return st;
}
