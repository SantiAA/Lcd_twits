#include<iostream>
#include"parseCmd.h"
#include "ParseCMDCallback.h"

#define INTERNAL_ERROR -1



enum kindOfError {
	NO_ERROR, UNKNOWN_ERROR, UNKNOWN_OPTION, PARAM_ATTEMPT
};	//Enum de tipos de errores posibles en la ejecucion

int is_known(const char *key, const char *knownOpt[], int size);
int strcicmp(char const *a, char const *b);

enum Parameters { USER, NUMBER };

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
				p2Struct->usr = (string)value;
				returnValue = true;
				break;
			case NUMBER:
				p2Struct->tweetCount = atoi(value);
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