#pragma once
#include <iostream>

enum class ErrType{NO_ERRORS, ERR_WHILE_CURL_INIT, ERR_WHILE_EASY_PERFORM, ERR_WHILE_MULTI_PERFORM, ERR_NO_URL_GIVEN, CHILD_ERROR};
class URLError
{
public:
	URLError();

	ErrType getErrType();
	void setErrType(ErrType type);
	std::string getErrDetail();
	void setErrDetail(std::string detail);

private:
	ErrType errorType;
	std::string errorDetail;
};