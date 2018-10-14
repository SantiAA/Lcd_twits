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
	//llamar a santi para que haga la animacion de carga
	//llamar a multi de facu
	return transit<WaitingForTweets>();
}

SC::result WaitingForTweets::doneReaction(const EventDoneTweets & event)
{
	//pasarle la lista de tweets a santi
	return transit<DisplayingTweets>();   //si ya termine paso a mostrar los tweets en la pantalla
}

SC::result WaitingForTweets::errorReaction(const ErrorEvent & event)
{
	//setear clase error adentro de fsm con la info
	return transit<End>();
}


/*DISPLAYING TWEETS STATE*/
DisplayingTweets::DisplayingTweets()
{
	cout << "Displaying tweets" << endl;
}

SC::result DisplayingTweets::refreshReaction(const EventRefresh & event)
{
	//avisar a santi que paso un tick
	return transit<DisplayingTweets>();
}

SC::result DisplayingTweets::nextReaction(const EventNext & event)
{
	//avisar a santi que tiene que mostrar el sig tweet
	return transit<DisplayingTweets>();
}

SC::result DisplayingTweets::previousReaction(const EventPrevious & event)
{
	//avisar a santi que tiene que mostrar el anterior tweet
	return transit<DisplayingTweets>();
}

SC::result DisplayingTweets::quitReaction(const EventQuit & event)
{
	//avisar a santi que apague todo,
	return transit<End>();
}

SC::result DisplayingTweets::repeatReaction(const EventRepeat & event)
{
	//avisar a santi que tiene que repetir
	return transit<DisplayingTweets>();
	
}

SC::result DisplayingTweets::incSpeedReaction(const EventIncSpeed & event)
{
	//aumentar la velocidad del timer
	return transit<DisplayingTweets>();
}

SC::result DisplayingTweets::decSpeedReaction(const EventDecSpeed & event)
{
	//disminuir la velocidad del timer
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

