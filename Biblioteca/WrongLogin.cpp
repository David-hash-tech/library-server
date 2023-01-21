#include "WrongLogin.h"
#include "SendMsg.h"

WrongLogin::WrongLogin() :AbsException(1, "Wrong username or password")
{

}

void WrongLogin::handleException(int Socket)
{
	SendMsg::getInstance()->Send(Socket, { this->msg });
}