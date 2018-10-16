#include "States.h"
//#include "FSM.h"

using namespace std;
/*INIT STATE*/
IniState::IniState()
{
}
SC::result IniState::react(const StartEvent & event)
{
	return transit<WaitingForTweets>();
}
/* WAITING FOR TWEETS  STATE*/
WaitingForTweets::WaitingForTweets()
{
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
	if (!context<TwitterFSM>().getHandler()->isOk())
	{
		string err = context<TwitterFSM>().getHandler()->getError().getErrDetail(); //ver que hacer aca!!!!
		context<TwitterFSM>().getUpdater()->showError(err);
	}
	context<TwitterFSM>().toggleDone();
	
	return transit<End>();
}

SC::result WaitingForTweets::react(const EventQuit & event)
{
	context<TwitterFSM>().toggleDone();
	return transit<End>();   //si apretan q mientras estoy descargando tweets cierro
}


/*DISPLAYING TWEETS STATE*/
DisplayingTweets::DisplayingTweets()
{
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
	context<TwitterFSM>().toggleDone();
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
	context<TwitterFSM>().toggleDone();
	return transit<End>();
}

SC::result DisplayingTweets::react(const ErrorEvent & event)
{
	if (!context<TwitterFSM>().getHandler()->isOk())
	{
		string err= context<TwitterFSM>().getHandler()->getError().getErrDetail(); //ver que hacer aca!!!!
		context<TwitterFSM>().getUpdater()->showError(err);
	}
	context<TwitterFSM>().toggleDone();
	return transit<End>();
}

/*END STATE*/
End::End()
{
}

