#include "QueryCreation.h"
#include "Logger.h"
#include "SendMsg.h"

QueryCreation::QueryCreation(std::string querytype):querytype(querytype)
{

}

void QueryCreation::handleException(int Socket)
{
	SendMsg::getInstance()->Send(Socket, { "QueryCreationError" });
	Logger::getInstance()->showMsg("Invalid " + this->querytype + " query was created!");
}
