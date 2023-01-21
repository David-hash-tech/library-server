#pragma once
#include "IUser.h"
#include <vector>

class UserScheduler
{
public:
	static IUser* getInstance(int Socket);
	static IUser* createInstance(IUser* user);
	static void destroyInstance(int Socket);

	static void login(int Socket, std::vector<std::string> MsgParts);
	static void inregistrare(int Socket, std::vector<std::string> MsgParts);

private:
	static IUser* instance[5];
	static const int MaxUsers = 5;

	UserScheduler() {};
	UserScheduler(const UserScheduler&) {};
	~UserScheduler() {};
};
