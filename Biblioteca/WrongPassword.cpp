#include "WrongPassword.h"
#include "SendMsg.h"

WrongPassword::WrongPassword() : AbsException(2, "Incorrect password")
{

}

void WrongPassword::handleException(int Socket)
{
	SendMsg::getInstance()->Send(Socket, { this->msg });
}
