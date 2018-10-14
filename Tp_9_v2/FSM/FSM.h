#pragma once
#include<iostream>
#include<boost/statechart/state_machine.hpp>
#include<boost/statechart/simple_state.hpp>
#include<boost/statechart/event.hpp>
#include<boost/statechart/transition.hpp>
#include<boost/statechart/custom_reaction.hpp>
#include"Events.h"
#include"States.h"
#include"../TweetHandler.h"

namespace SC = boost::statechart;


class InitState;
class TwitterFSM:public SC::state_machine<TwitterFSM,InitState>
{
public:
	TwitterFSM( ); //recibe tambien puntero a clase de facu, puntero a clase de santi 
	


private:
	
};