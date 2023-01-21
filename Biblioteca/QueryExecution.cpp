#include "QueryExecution.h"
#include "Logger.h"
#include "SendMsg.h"

QueryExecution::QueryExecution(std::string query): query(query)
{

}

void QueryExecution::handleException(int Socket)
{
	SendMsg::getInstance()->Send(Socket, { "QueryExecutionError" });
	Logger::getInstance()->showMsg("Unexpected error while executing query: \"" + this->query + "\"!");
}