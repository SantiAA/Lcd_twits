#include "FSM.h"
#include "States.h"

TwitterFSM::TwitterFSM(TweetHandler* handler_, DisplayUpdater* updater_)/*:eventGenerator(EventGenerator(this))*/
{
	(*this).initiate();
	(*this).process_event(StartEvent());
	handler = handler_;
	updater = updater_;
	done = false;
	//guardar todos los punteros
}

TweetHandler * TwitterFSM::getHandler()
{
	return handler;
}

DisplayUpdater * TwitterFSM::getUpdater()
{
	return updater;
}

/*void TwitterFSM::step()
{
	eventGenerator.generateEvents();
}*/

bool TwitterFSM::FSMdone()
{
	return done;
}

void TwitterFSM::toggleDone()
{
	done = !done;
}
