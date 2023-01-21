#pragma once
#include "string"

class Logger
{
private:
	static Logger* instance;

	Logger() { ; };
	~Logger() { ; };


public:
	static Logger* getInstance();
	static void destroyInstance();

	void showMsg(std::string msg);
};

