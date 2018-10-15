#include "Error.h"
using namespace std;
Error::Error()
{
	errorType = ErrorType::N_ERROR;
	errorDetail = string("NO_ERROR DEFAULT STRING");
}

ErrorType Error::getErrType()
{
	return errorType;
}



void Error::setErrType(ErrorType type)
{
	errorType = type;

}

std::string Error::getErrDetail()
{
	return errorDetail;
}

void Error::setErrDetail(std::string detail)
{
	errorDetail = detail;
}
