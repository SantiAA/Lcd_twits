#include "EventGenerator.h"
#include<conio.h>

#define TIMER_VALUE 1.0/60.0

EventGenerator::EventGenerator(TwitterFSM* FSM_)
{
	initAllegro();
	FSM = FSM_;
	fintweets = false;
}


EventGenerator::~EventGenerator()
{
	deInitAllegro();
}

void EventGenerator::generateEvents()
{
	if (_kbhit())
	{
		int pressedKey = _getch();
		switch (pressedKey)
		{
		case 's':
			FSM->process_event(EventNext());
			break;
		case 'a':
			FSM->process_event(EventPrevious());
			break;
		case'q':
			FSM->process_event(EventQuit());
			break;
		case 'r':
			FSM->process_event(EventRepeat());
			break;
		case '+':
			FSM->process_event(EventIncSpeed());
			break;
		case '-':
			FSM->process_event(EventDecSpeed());
			break;
		default:
			break;
		}
	}
	else if (!FSM->getHandler()->isOk() || !FSM->getUpdater()->isOk())
	{
		FSM->process_event(ErrorEvent());
	}
	else if (FSM->getUpdater()->finished()) //termine de escribir tweets en display 
	{
		FSM->process_event(EventLast());
	}

	else if (!FSM->getHandler()->isStillReceiving() && !fintweets) // termine de recibir tweets
	{
		fintweets = true;
		FSM->process_event(EventDoneTweets());
	}

	else if (!al_is_event_queue_empty(eventQueue))
	{
		ALLEGRO_EVENT ev;
		al_get_next_event(eventQueue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			FSM->process_event(EventRefresh());
		}
	}
	
}

bool EventGenerator::initAllegro()
{
	bool answer;
	if (al_init())
	{
		
		if ((refreshTimer = al_create_timer(TIMER_VALUE)) != NULL)
		{
			if ((eventQueue = al_create_event_queue()) != NULL)
			{
				al_register_event_source(eventQueue, al_get_timer_event_source(refreshTimer));
				al_start_timer(refreshTimer);
				answer = true;
			}
			else
			{
				err.setErrType(ErrorType::ALLEGRO_INIT_ERROR);
				err.setErrDetail("La inicializacion de allegro ha fallado");
				answer = false;
			}				
		}
		else
		{
			err.setErrType(ErrorType::ALLEGRO_INIT_ERROR);
			err.setErrDetail("La inicializacion de allegro ha fallado");
			answer = false;
		}		
	}
	else
	{
		err.setErrType(ErrorType::ALLEGRO_INIT_ERROR);
		err.setErrDetail( "La inicializacion de allegro ha fallado");
		answer = false;
	}
	return answer;
}

void EventGenerator::deInitAllegro()
{
	al_destroy_event_queue(eventQueue);
	al_destroy_timer(refreshTimer);
}
