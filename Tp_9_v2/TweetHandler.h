#pragma once
#include "URLHandler.h"
#include "json.hpp"
#include "Tweet.h"
#include <vector>

using namespace std;
using json = nlohmann::json;

// This is a class meant for handling Twitter's API specific requests. 
class TweetHandler : 
	public URLHandler
{
public:
	TweetHandler();
	TweetHandler(const char * account_, int tweetsN_ = 0);
	virtual ~TweetHandler();

	void setAccountSource(const char * account_);
	void setTweetsAmount(int tweetsN_);
	// To be called after setting new account and/or tweetsN. If constructed with constructor by default, this method bust be called so that there are no errors.
	void updateURL();

	// Must be called before any other request, to get the token from Twitter.
	bool createTwitterToken();
	// To be called after creating the token.
	bool setUpTwitterConnection();
	// To be called after setting up Twitter connection.
	vector<Tweet> getTweetsList();

private:
	void initQuery();

	string APIKey;
	string APISecretKey;
	string account;
	int tweetsN;
	json TwitterAnswer;
	// The token received from Twitter will be saved here.
	string token;
	// List containing all the tweets as strings.
	vector<Tweet> tweetsList;
	// This is the page from the API where the object will get the tweets from.
	string query;
};


/*

HOW TO IMPLEMENT THIS CLASS:

1.a. Construct with TweetHandler(char * account_, int tweetsN_ = 0)
  b. Construct with TweetHandler() and then call setAccountSource(char * account_) (setTweetsAmount(int tweetsN_) is optional).
	 After this, call updateURL().

2. Call isOK(). If it returns false, call getError().

3. Create token with createTwitterToken().

4. Set up Twitter connection with setUpTwitterConnection().

5. Write the following while loop:

	do
	{
		testHandler.multiPerform();
		// Here you can do whatever you want.
	} while (testHandler.isStillReceiving());

6. Get the information you want with getTweetsList().

*/