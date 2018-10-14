
//#include<boost/program_options/cmdline.hpp>
#include<boost/program_options.hpp>
#include<iostream>
#include"FSM/FSM.h"
namespace po = boost::program_options;
using namespace std;


int main(int argc, char*argv[])
{
	TwitterFSM myFsm;
	
	
	myFsm.process_event(EventDoneTweets()); 
	
	//parsear string
	//crear FSM
	//run fsm
	//buscar errores
	//Done!
}