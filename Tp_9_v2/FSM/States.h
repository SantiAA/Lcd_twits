#pragma once
#include<iostream>
#include<boost/statechart/state_machine.hpp>
#include<boost/statechart/simple_state.hpp>
#include<boost/statechart/event.hpp>
#include<boost/statechart/transition.hpp>
#include<boost/statechart/custom_reaction.hpp>
#include <boost/context/execution_context.hpp>
#include "Events.h"

namespace SC = boost::statechart; //short name
namespace MPL = boost::mpl;


class TwitterFSM;//foward declarations
class InitState;
class ParsingCMD;
class WaitingForTweets;
class ParsingJSON;
class DisplayingTweets;
class End;




class InitState : public SC::simple_state<InitState, TwitterFSM>
{
public:
	InitState();
	typedef SC::transition<StartEvent, ParsingCMD> reactions;
	
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
	SC::result refreshReaction(const EventRefresh& event);	//reacciones para cada evento
	SC::result doneReaction(const EventDoneTweets& event);
	SC::result errorReaction(const ErrorEvent& event);
	SC::result quitReaction(const EventQuit& event);
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
	SC::result refreshReaction(const EventRefresh& event);			//reacciones para cada evento
	SC::result nextReaction(const EventNext& event);
	SC::result previousReaction(const EventPrevious& event);
	SC::result quitReaction(const EventQuit& event);
	SC::result repeatReaction(const EventRepeat& event);
	SC::result incSpeedReaction(const EventIncSpeed& event);
	SC::result decSpeedReaction(const EventDecSpeed& event);
	SC::result lastReaction(const EventLast& event);
	SC::result errorReaction(const ErrorEvent& event);


};

class End : public SC::simple_state<End, TwitterFSM>
{
public:
	End();
};


