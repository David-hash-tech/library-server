#pragma once
#include "AbsException.h"

class UniqueUsername :
    public AbsException
{
private:
	std::string username;

public:
	UniqueUsername(std::string username);
	void handleException(int Socket) override;
};

