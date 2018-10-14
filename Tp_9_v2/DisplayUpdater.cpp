#include "DisplayUpdater.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>




DisplayUpdater::DisplayUpdater(BasicLCD * display, int fps)
{
	if (display->lcdInitOk())
	{
		lcd = display;
	}
	else
	{
		posibleErr.set_type(ErrType::LCD_NOT_FOUND);
	}
	speed = fps/2; //depende de los fps, inicialmente es dos veces por segundo (capaz es mucho)
	rRate = speed;
	state = 0;
	internalTweetList.clear();
	tweetNum = 0;
}


DisplayUpdater::~DisplayUpdater()
{
}

void DisplayUpdater::setTweets(vector<Tweet>& tweetList)
{
	internalTweetList = tweetList;
}

void DisplayUpdater::incSpeed()
{
	speed++;
}

void DisplayUpdater::decSpeed()
{
	if (speed > 1) // no puedo tener menos velocidad
	{
		speed--;
	}
}

void DisplayUpdater::repeatTweet()
{
	secondLinePos = 0; // reseteo el cursor
	rRate = speed;
}

bool DisplayUpdater::refreshDisplay(void)
{
	bool ret = true;
	if (rRate - 1 == 0) // me fijo si el contador llego a 0
	{
		lcd->lcdClear(); //limprio el display
		lcd->operator<<((const unsigned char *)firstLine.c_str()); // imprimo la fecha
		std::string temp(secondLine.substr(secondLinePos, 16)); //agarro 16 caracteres
		lcd->operator<< ((const unsigned char *)temp.c_str());
		secondLinePos++;
		if (secondLinePos > (secondLine.length() - 16)) // si ya termien de mostrar el tweet
		{
			if (tweetNum >= internalTweetList.size())
			{
				ret = false; // termine de mostrar todos lo tweets
			}
			else
			{
				setNextTweet();
				rRate = 2 * speed; // le da mas tiempo entre tweet y tweet 
			}
		}
		else
		{
			rRate = speed;
		}
	}
	else
		rRate--;

	return ret;

}

void DisplayUpdater::setWaiting(std::string accountName)
{
	size_t length = accountName.length();
	lcd->lcdClear();
	for (size_t i = 0; i < (16 - length) / 2; i++) // para mostrar el nombre centrado
	{
		lcd->lcdMoveCursorRight();
	}
	lcd->operator<<((const unsigned char *)accountName.c_str());
}

void DisplayUpdater::stillWaiting(void)
{
	cursorPosition cur = { 2,0 };
	if (rRate == 1)
	{
		lcd->lcdSetCursorPosition(cur);
		lcd->lcdClearToEOL();
		switch (state)
		{
		case 0:
			lcd->operator<<((const unsigned char *) "   Waiting");
			state++;
			break;
		case 1:
			lcd->operator<<((const unsigned char *) "   Waiting.");
			state++;
			break;
		case 2:
			lcd->operator<<((const unsigned char *) "   Waiting..");
			state++;
			break;
		case 3:
			lcd->operator<<((const unsigned char *) "   Waiting...");
			state = 0;
			break;
		default:
			lcd->operator<<((const unsigned char *) "I shdnt be here");
			state = 0;
			break;
		}
		rRate = speed;
	}
	else
		rRate--;
	
}

void DisplayUpdater::setNextTweet(void)
{
	string name = internalTweetList[tweetNum].getTwitter();
	string content = internalTweetList[tweetNum].getTweet();
	
	secondLine = name + string(":- ") + content + string("-                "); // el ultimo es para que quede el display vacio
	
	content = internalTweetList[tweetNum].getTweetedAt();
	content.erase(content.find_last_of(' ') - 5, 5); // le saco la parte del uso horario
	
	stringstream time(content.c_str());
	tm firstAtemp = {};
	time >> std::get_time(&firstAtemp, "%a %b %d %H:%M:%S %Y"); // ver si tengo el ultimo espacio
	time_t horario = mktime(&firstAtemp);

	name = content.substr(content.find_last_of(' ') - 5, 5); // cambio dependiendo del uso horario
	if (name[0] == '+')
	{
		horario += atoi(name.substr(1, 4).c_str()) * 3600;
	}
	else if (name[0] == '-')
	{
		horario -= atoi(name.substr(1, 4).c_str()) * 3600;
	}
	else
		std::cout << "le estoy errando" << std::endl;
	
	firstAtemp = *gmtime(&horario);
	char buffer[16];

	strftime(buffer, 16, "%D - %R",&firstAtemp);
	
	firstLine = string(buffer);
	secondLinePos = 0;
	tweetNum++;
}

bool DisplayUpdater::isOk()
{
	if (posibleErr.get_type() != ErrType::LCD_NO_ERROR)
	{
		return false;
	}
	else
		return true;
}

std::string DisplayUpdater::getError()
{
	return posibleErr.get_description();
}
