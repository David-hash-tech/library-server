#include "InvalidCommand.h"
#include "Logger.h"
#include "SendMsg.h"

InvalidCommand::InvalidCommand(int command) : AbsException(command, "Invalid command")
{

}

void InvalidCommand::handleException(int Socket)
{
	SendMsg::getInstance()->Send(Socket, { this->msg });
	Logger::getInstance()->showMsg("\"" + this->msg + "\"" + " pentru optiunea " + std::to_string(command));
}