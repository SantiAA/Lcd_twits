#include "TweetHandler.h"

#define API_KEY "7s8uvgQnJqjJDqA6JsLIFp90FcOaoR5Ic41LWyHOic0Ht3SRJ6"
#define API_SECRET_KEY "7s8uvgQnJqjJDqA6JsLIFp90FcOaoR5Ic41LWyHOic0Ht3SRJ6"


TweetHandler::TweetHandler() : tweetsList(), TwitterAnswer()
{
	APIKey = API_KEY;
	APISecretKey = API_SECRET_KEY;
	setTweetsAmount(0);
}

TweetHandler::TweetHandler(char * account_, int tweetsN_) : tweetsList(), TwitterAnswer()
{
	APIKey = API_KEY;
	APISecretKey = API_SECRET_KEY;
	setAccountSource(account_);
	setTweetsAmount(tweetsN_);

	updateURL();
}


TweetHandler::~TweetHandler()
{
}

void TweetHandler::setAccountSource(char * account_)
{
	account = account_;
}

void TweetHandler::setTweetsAmount(int tweetsN_)
{
	tweetsN = tweetsN_;
}

bool TweetHandler::createTwitterToken()
{
	string password = APIKey + ":" + APISecretKey;
	return easyPerform((char *)password.c_str());		// Executing an easyPerform to get the token using a password.
}

void TweetHandler::updateURL()
{
	initQuery();
	setURL((char *)query.c_str());						// Setting URL with parent method.
}

bool TweetHandler::setUpTwitterConnection()
{
	if (token.empty())
	{
		return false;						// If the token was not initialised, an empty vector is returned.
	}
	else
	{
		string aux = "Authorisation: Bearer ";
		aux += token;
		setUpMultiPerform((char *)aux.c_str());				// Setting up multi perform with the authentication header as specified by Twitter, using the token.
		return true;
	}
}

vector<Tweet> TweetHandler::getTweetsList()
{
	TwitterAnswer = json::parse(response);				// Parsing Twitter's response as a JSON object.
	try
	{
		for (auto tweetElement : TwitterAnswer)
		{
			string tweet = tweetElement["text"];
			int extended = tweet.find("https");
			tweet = tweet.substr(0, extended);			// The URL to continue reading the tweet gets eliminated.

			string twitter = tweetElement["screen_name"];
			string tweetedAt = tweetElement["created_at"];

			tweetsList.push_back(Tweet(tweet, twitter, tweetedAt));
		}
		return tweetsList;
	}
	catch (exception& e)
	{
		err.setErrType(ErrType::CHILD_ERROR);
		err.setErrDetail("Exception raised while parsing Twitter's JSON.");
		return vector<Tweet>();
	}
}

void TweetHandler::initQuery()
{
	query = string("https://api.twitter.com/1.1/statuses/user_timeline.json") + "?" + "screen_name=" + account;

	if (tweetsN != 0)
	{
		query += string("&") + "count=" + to_string(tweetsN);
	}
}
