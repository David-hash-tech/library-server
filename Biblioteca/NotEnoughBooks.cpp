#include "NotEnoughBooks.h"
#include "Logger.h"
#include "SendMsg.h"

NotEnoughBooks::NotEnoughBooks(std::string carte) : AbsException(11, "Not enough books")
{
}

void NotEnoughBooks::handleException(int Socket)
{
	SendMsg::getInstance()->Send(Socket, { this->msg });
	Logger::getInstance()->showMsg("Cartea " + this->carte + " nu mai are exemplare disponibile!");
}