
#pragma once
#include<iostream>
using namespace std;
typedef struct		//Estructura para informar tipo de error y detalles del error
{
	string errStr;
	unsigned int errorType;
}error_t;
typedef struct
{
	string usr;		//Nombre de usuario pasado por linea de comando
	int tweetCount;  //cantidad de tweets
	error_t error;		//Estructura de posibles errores de ejecucion   CAMBIAR ESTO
}userData_t;



int parseCallback(char *key, char *value, void *userData);
