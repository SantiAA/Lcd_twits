#include "URLError.h"
using namespace std;
URLError::URLError()
{
	errorType = ErrType::NO_ERRORS;
	errorDetail = string("NO_ERROR DEFAULT STRING");
}

ErrType URLError::getErrType()
{
	return errorType;
}



void URLError::setErrType(ErrType type)
{
	errorType = type;
	
}

std::string URLError::getErrDetail()
{
	return errorDetail;
}

void URLError::setErrDetail(std::string detail)
{
	errorDetail = detail;
}
