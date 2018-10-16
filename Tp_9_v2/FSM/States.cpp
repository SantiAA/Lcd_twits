#include "States.h"
//#include "FSM.h"

using namespace std;
/*INIT STATE*/
IniState::IniState()
{
	cout << "Init State"<<endl;
}
SC::result IniState::react(const StartEvent & event)
{
	return transit<WaitingForTweets>();
}
/* WAITING FOR TWEETS  STATE*/
WaitingForTweets::WaitingForTweets()
{
	cout << "Waiting for tweets" << endl;
}

SC::result WaitingForTweets::react(const EventRefresh & event)
{
	context<TwitterFSM>().getUpdater()->stillWaiting();   //llamar a santi para que haga la animacion de carga
	context<TwitterFSM>().getHandler()->multiPerform();//llamar a multi de facu
	return transit<WaitingForTweets>();
}

SC::result WaitingForTweets::react(const EventDoneTweets & event)
{
	vector<Tweet> temp=context<TwitterFSM>().getHandler()->getTweetsList();
	context<TwitterFSM>().getUpdater()->setTweets(temp);
	return transit<DisplayingTweets>();   //si ya termine paso a mostrar los tweets en la pantalla
}

SC::result WaitingForTweets::react(const ErrorEvent & event)
{
	
	//setear clase error adentro de fsm con la info
	return transit<End>();
}

SC::result WaitingForTweets::react(const EventQuit & event)
{
	//pasarle la lista de tweets a santi
	return transit<DisplayingTweets>();   //si ya termine paso a mostrar los tweets en la pantalla
}


/*DISPLAYING TWEETS STATE*/
DisplayingTweets::DisplayingTweets()
{
	cout << "Displaying tweets" << endl;
}

SC::result DisplayingTweets::react(const EventRefresh & event)
{
	context<TwitterFSM>().getUpdater()->refreshDisplay();
	return transit<DisplayingTweets>();
}

SC::result DisplayingTweets::react(const EventNext & event)
{
	context<TwitterFSM>().getUpdater()->next();//avisar a santi que tiene que mostrar el sig tweet FALTA!
	return transit<DisplayingTweets>();
}

SC::result DisplayingTweets::react(const EventPrevious & event)
{
	context<TwitterFSM>().getUpdater()->prev();//avisar a santi que tiene que mostrar el sig tweet FALTA!
	return transit<DisplayingTweets>();
}

SC::result DisplayingTweets::react(const EventQuit & event)
{
	//context<TwitterFSM>().done = true;
	return transit<End>();
}

SC::result DisplayingTweets::react(const EventRepeat & event)
{
	context<TwitterFSM>().getUpdater()->repeatTweet();//avisar a santi que tiene que repetir
	return transit<DisplayingTweets>();
	
}

SC::result DisplayingTweets::react(const EventIncSpeed & event)
{
	context<TwitterFSM>().getUpdater()->incSpeed();//aumentar la velocidad del timer
	return transit<DisplayingTweets>();
}

SC::result DisplayingTweets::react(const EventDecSpeed & event)
{
	context<TwitterFSM>().getUpdater()->decSpeed();//disminuir la velocidad del timer
	return transit<DisplayingTweets>();
}

SC::result DisplayingTweets::react(const EventLast & event)
{
	return transit<End>();
}

SC::result DisplayingTweets::react(const ErrorEvent & event)
{
	//setear clase error adentro de fsm con la info
	return transit<End>();
}

/*END STATE*/
End::End()
{
	cout << "End" << endl;
}

