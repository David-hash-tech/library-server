#pragma once
#include "AbsException.h"

class WrongUsername:
	public AbsException
{
private:
	std::string username;

public:
	WrongUsername(std::string username);
	void handleException(int Socket) override;
};

