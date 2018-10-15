#include "FSM.h"

TwitterFSM::TwitterFSM()
{
	(*this).initiate();
	(*this).process_event(StartEvent());
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
