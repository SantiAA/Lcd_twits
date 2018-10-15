
//#include<boost/program_options/cmdline.hpp>
#include<boost/program_options.hpp>
#include<iostream>
#include"FSM/FSM.h"
#include"DisplayUpdater.h"
#include"TweetHandler.h"
#include"ParseCMD.h"
#include "ParseCMDCallback.h"
namespace po = boost::program_options;
using namespace std;


int main(int argc, char*argv[])
{
	userData_t userData;
	userData.tweetCount = 0;
	if (parseCmdLine(argc, argv, parseCallback, &userData) == 0)
	{
		//error
	}
	TweetHandler handler((char*)(userData.usr.c_str()),userData.tweetCount);
	DisplayUpdater updater;
	updater.setWaiting(userData.usr);
	TwitterFSM myFsm(&handler,&updater);
	while (!myFsm.FSMdone())
	{
		myFsm.step();
	}
	
	
	
	//buscar errores
	//Done!
}