#include "Tweet.h"



Tweet::Tweet()
{
}

Tweet::Tweet(string tweet_, string twitter_, string tweetedAt_)
{
	setTweet(tweet_);
	setTwitter(twitter_);
	setTweetedAt(tweetedAt_);
}


Tweet::~Tweet()
{
}

string Tweet::getTweet()
{
	return tweet;
}

string Tweet::getTwitter()
{
	return twitter;
}

string Tweet::getTweetedAt()
{
	return tweetedAt;
}

void Tweet::setTweet(string tweet_)
{
	tweet = tweet_;
}

void Tweet::setTwitter(string twitter_)
{
	twitter = twitter_;
}

void Tweet::setTweetedAt(string tweetedAt_)
{
	tweetedAt = tweetedAt_;
}
