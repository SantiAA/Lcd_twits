#pragma once

#include <string>

using namespace std;

class Tweet
{
public:
	Tweet();
	Tweet(string tweet_, string twitter_, string tweetedAt_);
	~Tweet();

	string getTweet();
	string getTwitter();
	string getTweetedAt();

	void setTweet(string tweet_);
	void setTwitter(string twitter_);
	void setTweetedAt(string tweetedAt_);

private:
	string tweet;
	string twitter;
	string tweetedAt;
};

