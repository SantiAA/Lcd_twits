#pragma once
#include<iostream>
#include<boost/statechart/state_machine.hpp>
#include<boost/statechart/simple_state.hpp>
#include<boost/statechart/event.hpp>
#include<boost/statechart/transition.hpp>
#include<boost/statechart/custom_reaction.hpp>
#include"FSM.h"
#include "Events.h"

namespace SC = boost::statechart; //short name
namespace MPL = boost::mpl;


class TwitterFSM;//foward declarations
class IniState;
class ParsingCMD;
class WaitingForTweets;
class ParsingJSON;
class DisplayingTweets;
class End;

class TwitterFSM :public SC::state_machine<TwitterFSM, IniState>
{
public:
	TwitterFSM(TweetHandler* handler_, DisplayUpdater* updater_); //recibe tambien puntero a clase de facu, puntero a clase de santi 
	TweetHandler* getHandler();
	DisplayUpdater* getUpdater();
	//void step();
	bool FSMdone();


private:
	TweetHandler* handler;
	DisplayUpdater* updater;
	//EventGenerator eventGenerator;
	bool done;
};



class IniState : public SC::simple_state<IniState, TwitterFSM>
{
public:
	IniState();
	typedef SC::custom_reaction<StartEvent> reactions;
	SC::result react(const StartEvent& event);
};


class WaitingForTweets : public SC::simple_state<WaitingForTweets, TwitterFSM>
{
public:
	WaitingForTweets();
	typedef MPL::list <						//lista de eventos que pueden ser recibidos
		SC::custom_reaction<EventRefresh>,
		SC::custom_reaction<EventDoneTweets>,
		SC::custom_reaction<ErrorEvent>,
		SC::custom_reaction<EventQuit>
	>reactions;
	SC::result react(const EventRefresh& event);	//reacciones para cada evento
	SC::result react(const EventDoneTweets& event);
	SC::result react(const ErrorEvent& event);
	SC::result react(const EventQuit& event);
};

class DisplayingTweets : public SC::simple_state<DisplayingTweets, TwitterFSM>
{
public:
	DisplayingTweets();
	typedef MPL::list<							//lista de eventos que pueden ser recibidos
		SC::custom_reaction<EventRefresh>,
		SC::custom_reaction<EventNext>,
		SC::custom_reaction<EventPrevious>,
		SC::custom_reaction<EventQuit>,
		SC::custom_reaction<EventRepeat>,
		SC::custom_reaction<EventIncSpeed>,
		SC::custom_reaction<EventDecSpeed>,
		SC::custom_reaction<EventLast>,
		SC::custom_reaction<ErrorEvent>
	>reactions;
	SC::result react(const EventRefresh& event);			//reacciones para cada evento
	SC::result react(const EventNext& event);
	SC::result react(const EventPrevious& event);
	SC::result react(const EventQuit& event);
	SC::result react(const EventRepeat& event);
	SC::result react(const EventIncSpeed& event);
	SC::result react(const EventDecSpeed& event);
	SC::result react(const EventLast& event);
	SC::result react(const ErrorEvent& event);


};

class End : public SC::simple_state<End, TwitterFSM>
{
public:
	End();
};


