#pragma once

#include<iostream>

class CMDParser
{
public:
	CMDParser(int argc_, char **argv_);
	bool parse();
	
private:
	int argc;
	char **argv;

};

