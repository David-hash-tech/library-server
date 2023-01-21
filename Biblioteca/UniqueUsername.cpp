#include "UniqueUsername.h"
#include "SendMsg.h"

UniqueUsername::UniqueUsername(std::string msg) : AbsException(2, "Username unique")
{

}

void UniqueUsername::handleException(int Socket)
{
	SendMsg::getInstance()->Send(Socket, { this->msg });
}