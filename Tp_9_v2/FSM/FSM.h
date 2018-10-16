#pragma once
#include<iostream>
#include<boost/statechart/state_machine.hpp>
#include<boost/statechart/simple_state.hpp>
#include<boost/statechart/event.hpp>
#include<boost/statechart/transition.hpp>
#include<boost/statechart/custom_reaction.hpp>
#include"Events.h"
#include"../TweetHandler.h"
#include"../DisplayUpdater.h"

namespace SC = boost::statechart;

//extern class IniState;

//class IniState;
//class IniState : public SC::simple_state<IniState, TwitterFSM>
//{
//public:
//	IniState();
//	typedef SC::transition<StartEvent, WaitingForTweets> reactions;
//
//};



//class TwitterFSM:public SC::state_machine<TwitterFSM,IniState>
//{
//public:
//	TwitterFSM( TweetHandler* handler_, DisplayUpdater* updater_); //recibe tambien puntero a clase de facu, puntero a clase de santi 
//	TweetHandler* getHandler();
//	DisplayUpdater* getUpdater();
//	//void step();
//	bool FSMdone();
//
//
//private:
//	TweetHandler* handler;
//	DisplayUpdater* updater;
//	//EventGenerator eventGenerator;
//	bool done;
//};