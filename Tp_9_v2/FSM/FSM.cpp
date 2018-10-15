#include "FSM.h"

TwitterFSM::TwitterFSM(TweetHandler* handler_, DisplayUpdater* updater_):eventGenerator(this)
{
	(*this).initiate();
	(*this).process_event(StartEvent());
	handler = handler_;
	updater = updater_;
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

void TwitterFSM::step()
{
	eventGenerator.generateEvents();
}

bool TwitterFSM::FSMdone()
{
	return done;
}
