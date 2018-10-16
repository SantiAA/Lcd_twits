
//#include<boost/program_options/cmdline.hpp>
#include<boost/program_options.hpp>
#include<iostream>
#include"FSM/FSM.h"
#include"DisplayUpdater.h"
#include"TweetHandler.h"
#include"ParseCMD.h"
#include "ParseCMDCallback.h"
#include "EventGenerator.h"
#include "Display/delay.h"
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
	if (!handler.isOk())
	{
		cout << handler.getError().getErrDetail() << endl;
		return 0;
	}
	handler.createTwitterToken();
	handler.setUpTwitterConnection();
	handler.multiPerform();

	DisplayUpdater updater;
	updater.setWaiting(userData.usr);
	TwitterFSM myFsm(&handler,&updater);
	EventGenerator generator(&myFsm);
	
	while (!myFsm.FSMdone())
	{
		generator.generateEvents();
	}
	
	if (updater.finished())
	{
		updater.ultimoTweet();
	}
	
	delay(5000);
	std::cout << "Termino\n";
	
	//buscar errores
	//Done!
}