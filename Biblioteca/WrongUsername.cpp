#include "WrongUsername.h"
#include "SendMsg.h"

WrongUsername::WrongUsername(std::string msg) : AbsException(2, "Wrong username")
{

}

void WrongUsername::handleException(int Socket)
{
	SendMsg::getInstance()->Send(Socket, { this->msg });
}