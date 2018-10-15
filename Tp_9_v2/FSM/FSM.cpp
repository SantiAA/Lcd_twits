#include "FSM.h"

TwitterFSM::TwitterFSM(TweetHandler* handler_, DisplayUpdater* updater_)
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
