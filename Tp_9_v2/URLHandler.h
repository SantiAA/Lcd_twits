#pragma once

#include <string>
#include <curl.h>
#include "URLError.h"

using namespace std;

// This is a class meant for handling URL requests using libcurl library.
class URLHandler
{
public:
	URLHandler();
	URLHandler(char * URL_);
	virtual ~URLHandler();

	void setURL(char * URL_);

	char * getResponse();

	// This is a blocking perform.
	bool easyPerform();
	// For cases when password is needed, like asking for a token. This is a blocking perform.
	bool easyPerform(char * password);
	// This is for the set up of the non blocking perform.
	bool setUpMultiPerform();
	// For cases when a header is needed. This is for the set up of the non blocking perform.
	bool setUpMultiPerform(char * header);
	// Non blocking perform. Should be called in a while look while asking isStillReceiving().
	bool multiPerform();
	// To be asked in a while loop while multi performing.
	bool isStillReceiving();

	bool isOk();
	URLError getError();

protected:
	// To be called by the easyPerform. Contains the basic options for performing and performs.
	bool basicEasyPerform();
	// To be called by the multiPerform. Contains the basic options for performing.
	bool basicSetUpMultiPerform();

	// This handles all of the errors occurred during connection.
	URLError err;
	// URL that will be sent for the request.
	string URL;
	// The curl easy perform response will be saved here to see if there was an error while sending the request.
	CURLcode easyRes;
	// The curl multi perform response will be saved here to see if there was an error while sending the request.
	CURLMcode multiRes;
	// Request configurations will he saved here.
	CURL * curl;
	// This variable is necessary for using curl_multi_perform() (the non blocking way of emitting requests). Many easy handles will be attached to it.
	CURLM * multiHandle;
	// String containing response form API.
	string response;
	// Variable that indicates if multi perform is still receiving.
	int stillReceiving;

};

