#pragma once
#include <winsock.h>

class IUser;
class IException
{
public:
	virtual void handleException(int Socket) = 0;
};