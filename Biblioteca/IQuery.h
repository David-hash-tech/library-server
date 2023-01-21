#pragma once
#include "DataBaseConn.h"

class IQuery
{
public:

	virtual const std::string&  getQName() = 0;
	virtual void setQName(std::string name) = 0;

	virtual std::string createQuery() = 0;
	virtual void addPar(std::string par) = 0;
	virtual void executeQuery(std::string query, SQLHANDLE StmtHandle, std::string state = "", int command = 0) = 0;
};