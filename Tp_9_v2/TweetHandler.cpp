#include "TweetHandler.h"

#define API_KEY "HCB39Q15wIoH61KIkY5faRDf6"
#define API_SECRET_KEY "7s8uvgQnJqjJDqA6JsLIFp90FcOaoR5Ic41LWyHOic0Ht3SRJ6"


TweetHandler::TweetHandler() : tweetsList(), TwitterAnswer()
{
	APIKey = API_KEY;
	APISecretKey = API_SECRET_KEY;
	setTweetsAmount(0);
}

TweetHandler::TweetHandler(const char * account_, int tweetsN_) : tweetsList(), TwitterAnswer()
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

void TweetHandler::setAccountSource(const char * account_)
{
	account = account_;
}

void TweetHandler::setTweetsAmount(int tweetsN_)
{
	tweetsN = tweetsN_;
}

bool TweetHandler::createTwitterToken()
{
	setURL("https://api.twitter.com/oauth2/token");
	string password = APIKey + ":" + APISecretKey;
	bool ret = easyPerform(password.c_str());		// Executing an easyPerform to get the token using a password.

	TwitterAnswer = json::parse(response);
	try
	{
		string aux = TwitterAnswer["access_token"];
		token = aux;
	}
	catch (exception& e)
	{
		err.setErrType(ErrType::CHILD_ERROR);
		err.setErrDetail(string("Exception raised while parsing Twitter's JSON.") + e.what());
		return false;
	}

	updateURL();
	return ret;
}

void TweetHandler::updateURL()
{
	initQuery();
	setURL(query.c_str());						// Setting URL with parent method.
}

bool TweetHandler::setUpTwitterConnection()
{
	if (token.empty())
	{
		return false;						// If the token was not initialised, an empty vector is returned.
	}
	else
	{
		string aux = "Authorization: Bearer ";
		aux += token;
		setUpMultiPerform(aux.c_str());				// Setting up multi perform with the authentication header as specified by Twitter, using the token.
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

			string tweetedAt = tweetElement["created_at"];
			string twitter = tweetElement["user"]["name"];

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
