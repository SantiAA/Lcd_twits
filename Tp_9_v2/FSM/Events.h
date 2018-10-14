#pragma once
#include<iostream>
#include<boost/statechart/state_machine.hpp>
#include<boost/statechart/simple_state.hpp>
#include<boost/statechart/event.hpp>
#include<boost/statechart/transition.hpp>
#include<boost/statechart/custom_reaction.hpp>

namespace SC = boost::statechart; //short name
class StartEvent : public SC::event<StartEvent>
{

};

class EventDoneTweets : public SC::event<EventDoneTweets>
{

};

class ErrorEvent : public SC::event<ErrorEvent>
{
	
};

class EventRefresh : public SC::event<EventRefresh>
{
	
};

class EventNext : public SC::event<EventNext>
{

};

class EventPrevious : public SC::event<EventPrevious>
{

};

class EventQuit : public SC::event<EventQuit>
{

};

class EventRepeat : public SC::event<EventRepeat>
{

};

class EventIncSpeed : public SC::event<EventIncSpeed>
{

};

class EventDecSpeed : public SC::event<EventDecSpeed>
{

};

class EventLast : public SC::event<EventLast>
{

};