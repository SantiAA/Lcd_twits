#include<iostream>
#include"parseCmd.h"

#define INTERNAL_ERROR -1

typedef struct
{
	string mode;		//Modo de simulacion pasada por linea de comando
	int botCount;		//Cantidad de robots pasados por linea de comando	
	int heigthTiles;	//Cantidad de baldosas en altura pasadas por linea de comando
	int widthTiles;		//Cantidad de baldosas en ancho pasadas por linea de comando
	error_t error;		//Estructura de posibles errores de ejecucion   CAMBIAR ESTO
}userData_t;

typedef struct		//Estructura para informar tipo de error y detalles del error
{
	string errStr;
	unsigned int errorType;
}error_t;

enum kindOfError {
	NO_ERROR, NO_MEMORY, INVALID_WH_VALUE, WRONG_WTILES, WRONG_HTILES, WRONG_BCOUNT, WRONG_MODE_INPUT, UNKNOWN_ERROR
	, UNKNOWN_OPTION, PARAM_ATTEMPT, NO_WTILES, NO_HTILES, NO_BOTCOUNT, NO_MODE_INPUT, AL_INIT_FAIL
	, PRIMITIVE_FAIL, IMAGE_FAIL, TTF_FAIL, ALLEGRO_DISPLAY_ERROR, ALLEGRO_FONT_ERROR, ALLEGRO_IMAGE_LOAD_ERROR
};	//Enum de tipos de errores posibles en la ejecucion

int is_known(const char *key, const char *knownOpt[], int size);
int strcicmp(char const *a, char const *b);
int parseCallback(char *key, char *value, void *userData);
 enum Parameters{USER,NUMBER};

using namespace std;
int parseCallback(char *key, char *value, void *userData)
{
	userData_t *p2Struct = (userData_t*)userData;//casteo del puntero a estructura
	const char *knownOptions[] = { "user","number" };
	int receivedOpt;
	int returnValue;
	if (key != NULL)
	{
		if ((receivedOpt = is_known(key, knownOptions, sizeof(knownOptions) / sizeof(knownOptions[1]))) != INTERNAL_ERROR)// si key coincide con materia le asigno su valor
		{
			switch (receivedOpt)
			{
			case USER:
				p2Struct->mode = (string)value;
				returnValue = true;
				break;
			case NUMBER:
				p2Struct->botCount = atoi(value);
				returnValue = true;
				break;
			
			default:
				p2Struct->error.errorType = UNKNOWN_ERROR;
				p2Struct->error.errStr = "don't know what happened\n";
				returnValue = false;
				break;

			}
		}
		else
		{
			p2Struct->error.errorType = UNKNOWN_OPTION;
			p2Struct->error.errStr = "Una de las opciones ingresadas no es valida\n";
			returnValue = false;
		}
	}
	else
	{
		p2Struct->error.errorType = PARAM_ATTEMPT;
		p2Struct->error.errStr = "Se ingreso un parametro, por favor solo ingrese opciones\n";
		returnValue = false;
	}
	return returnValue;
}

int is_known(const char *key, const char *knownOpt[], int size)
{
	int i;
	int ready = 0;
	for (i = 0; i < size && !ready; i++)
	{
		if (!strcicmp(key, knownOpt[i]))
		{
			ready = 1;
		}

	}
	return ready ? i - 1 : INTERNAL_ERROR;
}

int strcicmp(char const *a, char const *b)
{
	for (;; a++, b++)
	{
		int d = tolower(*a) - tolower(*b);
		if (d != 0 || !*a)
		{
			return d;
		}
	}
}