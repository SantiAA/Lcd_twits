#include "States.h"
using namespace std;
/*INIT STATE*/
InitState::InitState()
{
	cout << "Init State"<<endl;
}
/* WAITING FOR TWEETS  STATE*/
WaitingForTweets::WaitingForTweets()
{
	cout << "Waiting for tweets" << endl;
}

SC::result WaitingForTweets::refreshReaction(const EventRefresh & event)
{
	context<TwitterFSM>().getUpdater()->stillWaiting();   //llamar a santi para que haga la animacion de carga
	context<TwitterFSM>().getHandler()->multiPerform();//llamar a multi de facu
	return transit<WaitingForTweets>();
}

SC::result WaitingForTweets::doneReaction(const EventDoneTweets & event)
{
	vector<Tweet> temp=context<TwitterFSM>().getHandler()->getTweetsList();
	context<TwitterFSM>().getUpdater()->setTweets(temp);
	//pasarle la lista de tweets a santi
	return transit<DisplayingTweets>();   //si ya termine paso a mostrar los tweets en la pantalla
}

SC::result WaitingForTweets::errorReaction(const ErrorEvent & event)
{
	//setear clase error adentro de fsm con la info
	return transit<End>();
}

SC::result WaitingForTweets::quitReaction(const EventQuit & event)
{
	//pasarle la lista de tweets a santi
	return transit<DisplayingTweets>();   //si ya termine paso a mostrar los tweets en la pantalla
}


/*DISPLAYING TWEETS STATE*/
DisplayingTweets::DisplayingTweets()
{
	cout << "Displaying tweets" << endl;
}

SC::result DisplayingTweets::refreshReaction(const EventRefresh & event)
{
	context<TwitterFSM>().getUpdater()->refreshDisplay();
	return transit<DisplayingTweets>();
}

SC::result DisplayingTweets::nextReaction(const EventNext & event)
{
	context<TwitterFSM>().getUpdater();//avisar a santi que tiene que mostrar el sig tweet FALTA!
	return transit<DisplayingTweets>();
}

SC::result DisplayingTweets::previousReaction(const EventPrevious & event)
{
	//avisar a santi que tiene que mostrar el anterior tweetFALTA!
	return transit<DisplayingTweets>();
}

SC::result DisplayingTweets::quitReaction(const EventQuit & event)
{
	//avisar a santi que apague todo,
	return transit<End>();
}

SC::result DisplayingTweets::repeatReaction(const EventRepeat & event)
{
	context<TwitterFSM>().getUpdater()->repeatTweet();//avisar a santi que tiene que repetir
	return transit<DisplayingTweets>();
	
}

SC::result DisplayingTweets::incSpeedReaction(const EventIncSpeed & event)
{
	context<TwitterFSM>().getUpdater()->incSpeed();//aumentar la velocidad del timer
	return transit<DisplayingTweets>();
}

SC::result DisplayingTweets::decSpeedReaction(const EventDecSpeed & event)
{
	context<TwitterFSM>().getUpdater()->decSpeed;//disminuir la velocidad del timer
	return transit<DisplayingTweets>();
}

SC::result DisplayingTweets::lastReaction(const EventLast & event)
{
	return transit<End>();
}

SC::result DisplayingTweets::errorReaction(const ErrorEvent & event)
{
	//setear clase error adentro de fsm con la info
	return transit<End>();
}

/*END STATE*/
End::End()
{
	cout << "End" << endl;
}

