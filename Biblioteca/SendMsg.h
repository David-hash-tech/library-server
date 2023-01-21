#pragma once
#include <vector>
#include <string>

class SendMsg
{
private:
	char MsgToClient[256];
	static SendMsg* instance;

	SendMsg() { ; };
	~SendMsg() { ; };


public:
		static SendMsg* getInstance();
	static void destroyInstance();
	
	void Send(int Socket, std::vector<std::string> parameters);
};

