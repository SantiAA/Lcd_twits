#pragma once
#include"FSM/FSM.h"
#include"allegro5/allegro.h"
#include"allegro5/events.h"
#include"Error.h"
class EventGenerator
{
public:
	EventGenerator(TwitterFSM* FSM_);
	~EventGenerator();

	void generateEvents();
private:
	TwitterFSM* FSM;
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_TIMER* refreshTimer;
	Error err;
	bool initAllegro();
	void deInitAllegro();
};

