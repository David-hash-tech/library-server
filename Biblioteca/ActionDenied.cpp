#include "ActionDenied.h"
#include "Logger.h"
#include "SendMsg.h"

ActionDenied::ActionDenied(int command) :AbsException(command, "Action Denied")
{

}

void ActionDenied::handleException(int Socket)
{
	SendMsg::getInstance()->Send(Socket, { this->msg });
	Logger::getInstance()->showMsg("\"Action Denied\" pentru optiunea " + std::to_string(command));
}