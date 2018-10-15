#include "URLHandler.h"
#include <functional>

#define _CRT_SECURE_NO_WARNINGS

// Callback function to register curl's response.
static size_t curlCallback(void *contents, size_t size, size_t nmemb, void *userp);

URLHandler::URLHandler() : err()
{
	stillReceiving = 0;
	response = "";
	err.setErrType(ErrType::ERR_NO_URL_GIVEN);		// When initialised without a URL, an error is raised, making sure to remind the user that he must set a URL manually.
}

URLHandler::URLHandler(const char * URL_) : err()
{
	setURL(URL_);
	stillReceiving = 0;
	response = "";
}


URLHandler::~URLHandler()
{
}

void URLHandler::setURL(const char * URL_)
{
	URL = URL_;
	err.setErrType(ErrType::NO_ERRORS);
}

char * URLHandler::getResponse()
{
	return (char *)response.c_str();
}

bool URLHandler::easyPerform()
{
	curl = curl_easy_init();		// Initialising curl.
	response = "";					// Initialising response string.
	
	if (curl)						// As long as everything was ok...
	{
		return basicEasyPerform();
	}
	else
	{
		err.setErrType(ErrType::ERR_WHILE_CURL_INIT);
		curl_easy_cleanup(curl);
		return false;
	}
}

bool URLHandler::easyPerform(const char * password)
{
	curl = curl_easy_init();		// Initialising curl.
	response = "";					// Initialising response string.

	if (curl)						// as long as everything was ok...
	{
		curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);							// Basic authentication by HTTP.
		curl_easy_setopt(curl, CURLOPT_USERPWD, password);

		struct curl_slist * list = NULL;													// List for setting up a header.
		list = curl_slist_append(list, "Content-Type: application/x-www-form-urlencoded;charset=UTF-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);									// Telling CURL we're sending coded URLs and in	UTF8 format. This automatically codes our password.

		string data = "grant_type=client_credentials";
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());							// Telling CURL we're working with credentials.
		
		return basicEasyPerform();
	}
	else
	{
		err.setErrType(ErrType::ERR_WHILE_CURL_INIT);
		curl_easy_cleanup(curl);
		return false;
	}
}

bool URLHandler::setUpMultiPerform()
{
	curl = curl_easy_init();								// Initialising curl.
	multiHandle = curl_multi_init();						// Initialising multiHandle.
	response = "";											// Initialising response string.
	stillReceiving = 0;

	if (curl != NULL && multiHandle != NULL)				// As long as everything is ok...
	{
		return basicSetUpMultiPerform();
	}
	else
	{
		err.setErrType(ErrType::ERR_WHILE_CURL_INIT);
		curl_easy_cleanup(curl);
		return false;
	}
}

bool URLHandler::setUpMultiPerform(const char * header)
{
	curl = curl_easy_init();								// Initialising curl.
	multiHandle = curl_multi_init();						// Initialising multiHandle.
	response = "";											// Initialising response string.
	stillReceiving = 0;

	if (curl != NULL && multiHandle != NULL)				// As long as everything is ok...
	{
		struct curl_slist * list = NULL;													// List for setting up a header.
		list = curl_slist_append(list, header);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);									// Telling curl we're adding a header.
		
		return basicSetUpMultiPerform();
	}
	else
	{
		err.setErrType(ErrType::ERR_WHILE_CURL_INIT);
		curl_easy_cleanup(curl);
		return false;
	}
}

bool URLHandler::multiPerform()
{
	multiRes = curl_multi_perform(multiHandle, &stillReceiving);		// Performs.
	if (multiRes != CURLE_OK)											// Notifies if there was an error.
	{
		err.setErrType(ErrType::ERR_WHILE_MULTI_PERFORM);
		curl_easy_cleanup(curl);
		return false;
	}
	else
	{
		if (!stillReceiving)											// Cleans up when finished receiving.
		{
			curl_easy_cleanup(curl);
			curl_multi_cleanup(multiHandle);
		}
		return true;
	}
}

bool URLHandler::isStillReceiving()
{
	return stillReceiving;
}

bool URLHandler::isOk()
{
	if (err.getErrType() != ErrType::NO_ERRORS)
	{
		return false;
	}
	else
	{
		return true;
	}
}

URLError URLHandler::getError()
{
	return err;
}

bool URLHandler::basicEasyPerform()
{
	curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());											// Setting URL we will connect to.
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);									// Telling CURL to follow redirection in case page we visit redirects us somewhere else.
	curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);		// Telling CURL to work with either HTTP or HTTPS.

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallback);					// Specifying callback function to be called when curl has to write the response.
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);								// Specifying "response" as the parameter to be passed to callback function as user data.

	easyRes = curl_easy_perform(curl);														// Performing in blocking mode.
	if (easyRes != CURLE_OK)
	{
		err.setErrType(ErrType::ERR_WHILE_EASY_PERFORM);
		err.setErrDetail(curl_easy_strerror(easyRes));
		curl_easy_cleanup(curl);
		return false;
	}

	curl_easy_cleanup(curl);
	return true;
}

bool URLHandler::basicSetUpMultiPerform()
{
	curl_multi_add_handle(multiHandle, curl);			// Attaching easy handle to multi handle to perform non blocking.

	curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());											// Setting URL we will connect to.
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);									// Telling CURL to follow redirection in case page we visit redirects us somewhere else.
	curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);		// Telling CURL to work with either HTTP or HTTPS.

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallback);						// Specifying callback function to be called when curl has to write the response.
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);								// Specifying "response" as the parameter to be passed to callback function as user data.

	return true;
}


/*          CALLBACK FUNCTION TO BE PASSED TO CURL AS A PARAMETER           */
static size_t curlCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	char* data = (char *)contents;
	std::string* s = (std::string*)userp;
	s->append(data, realsize);
	return realsize;
}
