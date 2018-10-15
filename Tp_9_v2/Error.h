#pragma once
#include<iostream>

enum class ErrorType {
	N_ERROR, ALLEGRO_INIT_ERROR, ALLEGRO_DISPLAY_ERROR, ALLEGRO_QUEUE_ERROR, ALLEGRO_FAILED_IMAGE_LOAD, ALLEGRO_FAILED_FONT_LOAD
	, UI_NOT_CREATED, UI_CREATED, NO_IMAGES_ADDED, ERROR_PNG
};
class Error
{
public:
	Error();

	ErrorType getErrType();
	void setErrType(ErrorType type);
	std::string getErrDetail();
	void setErrDetail(std::string detail);

private:
	ErrorType errorType;
	std::string errorDetail;
};