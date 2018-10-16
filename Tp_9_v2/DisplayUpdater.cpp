 #include "DisplayUpdater.h"
#include "Display/HD44780LCD.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS 1

#pragma warning(disable:4996) // para que no tiere el warning de visual pq no le gusta gmtime

BasicLCD * getDisplay();

DisplayUpdater::DisplayUpdater( int fps)
{
	BasicLCD * display = getDisplay();

	if (display->lcdInitOk())
	{
		lcd = display;
	}
	else
	{
		posibleErr.set_type(ErrrType::LCD_NOT_FOUND);
	}
	speed = fps; //depende de los fps, inicialmente es dos veces por segundo (capaz es mucho)
	rRate = speed;
	state = 0;
	internalTweetList.clear();
	tweetNum = 0;
	waitMoving = false;
	direction = false;
	termine = false;
}


DisplayUpdater::~DisplayUpdater()
{
	delete lcd;
}

void DisplayUpdater::setTweets(vector<Tweet>& tweetList)
{
	internalTweetList = tweetList;
	if (!internalTweetList.empty())
	{
		setNextTweet();//guardo el primer tweet para mostrar
	}
}

void DisplayUpdater::showError(string & error_) // procurar errores de 32 chars
{
	lcd->lcdClear();
	lcd->operator<<((const unsigned char * )error_.c_str());
}

void DisplayUpdater::incSpeed()
{
	if ( (speed * 0.9)  > 1) // no puedo tener menos velocidad
	{
		speed -= speed * 0.1;
	}
}

void DisplayUpdater::decSpeed()
{
	speed += speed * 0.1;
}

void DisplayUpdater::repeatTweet()
{
	secondLinePos = 0; // reseteo el cursor
	rRate = speed;
}

void DisplayUpdater::next()
{
	if (tweetNum >= internalTweetList.size())
	{
		termine = true; // termine de mostrar todos lo tweets
		lcd->operator<<((const unsigned char *)"   No more         Tweets.");
	}
	else
	{
		lcd->lcdClear();
		setNextTweet();
		rRate = 2 * speed; // le da mas tiempo entre tweet y tweet 
	}
}

void DisplayUpdater::prev()
{
	if (tweetNum >= 2)
	{
		tweetNum-=2; //como tweet num apunta al siguente a mostrar, vuelvo dos para ver el anterior
		lcd->lcdClear();
		setNextTweet();
	}
	else
	{
		this->repeatTweet();
	}
}

void DisplayUpdater::refreshDisplay(void)
{
	if (rRate - 1 == 0) // me fijo si el contador llego a 0
	{
		cursorPosition cur = { 2,0 };

		lcd->lcdSetCursorPosition(cur);
		lcd->lcdClearToEOL();

		std::string temp(secondLine.substr(secondLinePos, 16)); //agarro 16 caracteres
		lcd->operator<< ((const unsigned char *)temp.c_str());
		secondLinePos++;
		if (secondLinePos > (secondLine.length() - 16)) // si ya termien de mostrar el tweet
		{
			if (tweetNum >= internalTweetList.size())
			{
				termine = true; // termine de mostrar todos lo tweets
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

}

void DisplayUpdater::setWaiting(std::string accountName)
{
	size_t length = accountName.length();
	lcd->lcdClear();
	if (length <= 16)
	{
		for (size_t i = 0; i < (16 - length) / 2; i++) // para mostrar el nombre centrado
		{
			lcd->lcdMoveCursorRight();
		}
		lcd->operator<<((const unsigned char *)accountName.c_str());
	}
	else
	{
		waitMoving = true;
		firstLine = accountName;
		lcd->operator<<((const unsigned char *)firstLine.substr(0,16).c_str());
		secondLinePos = 1; // lo uso para marcar en que parte estoy
	}

	cursorPosition cur = { 2,0 };
	
	lcd->lcdSetCursorPosition(cur);
	lcd->lcdClearToEOL();
	lcd->operator<<((const unsigned char *) "Waiting");
	rRate = speed / 5;
	state++;


}

void DisplayUpdater::stillWaiting(void)
{
	if (waitMoving && (rRate == 1)) //Si el nombre es muy largo lo muevo como marquesina
	{
		lcd->lcdClear();
		lcd->operator<<((const unsigned char *)firstLine.substr(secondLinePos, 16).c_str());
		
		if (direction) //true derecha
		{
			if (secondLinePos >= 1) // todavia tengo para moverme a la derecha
			{
				secondLinePos--;
			}
			else
			{
				direction = !direction;
			}
		}
		else //false izquierda
		{
			if (firstLine.length() - secondLinePos - 1 >= 16) // si me quedan mas de 16 caracteres sigo moviendo 
			{
				secondLinePos++;
			}
			else
			{
				direction = !direction;// cambio de direccion
			}
		}
	}

	cursorPosition cur = { 2,7 };
	if (rRate == 1)
	{
		lcd->lcdSetCursorPosition(cur);
		lcd->lcdClearToEOL();
		switch (state)
		{
		case 0:
			lcd->operator<<((const unsigned char *) " ");
			state++;
			break;
		case 1:
			lcd->operator<<((const unsigned char *) ".");
			state++;
			break;
		case 2:
			lcd->operator<<((const unsigned char *) "..");
			state++;
			break;
		case 3:
			lcd->operator<<((const unsigned char *) "...");
			state = 0;
			break;
		default:
			lcd->operator<<((const unsigned char *) "I shdnt be here");
			state = 0;
			break;
		}
		rRate = speed/5;
	}
	else
		rRate--;
	
}

void DisplayUpdater::setNextTweet(void)
{
	string name = internalTweetList[tweetNum].getTwitter();
	string content = internalTweetList[tweetNum].getTweet();
	
	for (int i = 0; i<name.length();i++)
	{
		switch (name[i])
		{
		case 'á': name[i] = 'a'; break;
		case 'é': name[i] = 'e'; break;
		case 'í': name[i] = 'i'; break;
		case 'ó': name[i] = 'o'; break;
		case 'ú': name[i] = 'u'; break;
		case 'ñ': name[i] = 'n'; break;
		case 'Á': name[i] = 'A'; break;
		case 'É': name[i] = 'E'; break;
		case 'Í': name[i] = 'I'; break;
		case 'Ó': name[i] = 'O'; break;
		case 'Ú': name[i] = 'U'; break;
		case 'Ñ': name[i] = 'N'; break;
		default: break;
		}
	}
	for (int i = 0; i < content.length(); i++)
	{
		switch (content[i])
		{
		case 'á': content[i] = 'a'; break;
		case 'é': content[i] = 'e'; break;
		case 'í': content[i] = 'i'; break;
		case 'ó': content[i] = 'o'; break;
		case 'ú': content[i] = 'u'; break;
		case 'ñ': content[i] = 'n'; break;
		case 'Á': content[i] = 'A'; break;
		case 'É': content[i] = 'E'; break;
		case 'Í': content[i] = 'I'; break;
		case 'Ó': content[i] = 'O'; break;
		case 'Ú': content[i] = 'U'; break;
		case 'Ñ': content[i] = 'N'; break;
		default: break;
		}
	}
	
	secondLine = name + string(": - ") + content + string(" -                "); // el ultimo es para que quede el display vacio
	
	content = internalTweetList[tweetNum].getTweetedAt();
	content.erase(content.find_last_of(' ') - 5, 5); // le saco la parte del uso horario
	
	stringstream time(content.c_str());
	struct tm firstAtemp = {};
	time >> std::get_time(&firstAtemp, "%a %b %d %H:%M:%S %Y"); // ver si tengo el ultimo espacio
	time_t horario = mktime(&firstAtemp);

	content = internalTweetList[tweetNum].getTweetedAt();
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
	
	firstAtemp = *localtime(&horario);
	char buffer[17];

	strftime(buffer, 17, "%d/%m/%y - %H:%M",&firstAtemp);
	
	firstLine = string(buffer);
	secondLinePos = 0;
	tweetNum++;

	lcd->lcdClear(); //limprio el display
	lcd->operator<<((const unsigned char *)firstLine.c_str()); // imprimo la fecha

}

bool DisplayUpdater::finished()
{
	return termine;
}

bool DisplayUpdater::isOk()
{
	if (posibleErr.get_type() != ErrrType::LCD_NO_ERROR)
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

void DisplayUpdater::ultimoTweet()
{
	lcd->lcdClear();
	lcd->operator<<((const unsigned char *)"Ultimo Tweet");
}

BasicLCD * getDisplay(void)
{
	return new HD44780LCD();
}