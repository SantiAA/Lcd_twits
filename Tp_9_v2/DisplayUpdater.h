#pragma once
#include <string>
#include <vector>
#include "Display\BasicLCD.h"
#include "Display/ErrLCD.h"
#include "Tweet.h"

class DisplayUpdater
{
public:
	
	DisplayUpdater(int fps = 60);
	~DisplayUpdater();

	void setTweets(vector<Tweet>& tweetList); // ver que formato de cosa recibe
	
	void showError(string& error_);
	
	void incSpeed();
	void decSpeed();
	void repeatTweet();
	void next();
	void prev();

	void refreshDisplay(void);

	void setWaiting(std::string accountName); // este seria para el principio
	void stillWaiting(void);// esta es la que va a ir moviendo la señal
	
	bool finished();
	
	bool isOk(void);
	std::string getError();
	
private:

	void setNextTweet(void);

	bool termine;

	int speed; //con 60FPS, cada cuantos FPS se refreshea
	int rRate; // cuantos FPS le faltan para volver a refrescar

	BasicLCD * lcd;

	std::string firstLine; // contenido de la primera linea
	std::string secondLine; // tweet a mostrar
	
	size_t secondLinePos; // posicion del tweet a partir de la cual estoy mostrando
	vector<Tweet> internalTweetList;
	ErrLCD posibleErr;

	char tweetNum;
	char state;

	bool waitMoving;
	bool direction; //true derecha, false izq
};

