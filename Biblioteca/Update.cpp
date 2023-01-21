#include "Update.h"
#include "QueryCreation.h"
#include "QueryExecution.h"


Update::Update() :AbsQuery("Update")
{

}

Update::Update(std::vector<std::string> parameters) : AbsQuery("Update", parameters)
{

}


void Update::setQName(std::string name)
{
	this->QName = name;
}

const std::string& Update::getQName()
{
	return this->QName;
}


void Update::addPar(std::string par)
{
	this->parameters.push_back(par);
}

std::string Update::createQuery()
{
	std::string query;

	switch (parameters.size())
	{
	case 4:
		query = "update " + parameters[0] + " set " + parameters[1] + " = '" + parameters[2] + "' where ID_" + parameters[0] + "= '" + parameters[3] + "'";
		break;

	case 6:
		if (parameters[3] == "search")
			query = "update " + parameters[0] + " set " + parameters[1] + " = '" + parameters[2] + "' where " + parameters[4] + "= '" + parameters[5] + "'";
		break;

	case 9:
		query = "update " + parameters[0] + " set " + parameters[1] + " = DATEADD(day, " + parameters[2] + ", " + parameters[1] + ") where " + parameters[4] + "= '" + parameters[5] + "' and " + parameters[7] + "= '" + parameters[8] + "'";
		break;

	default:
		throw QueryCreation("Update");
		break;
	}

	return query;
	/*
		in vectorul parameters:
			poz 0 -> tabelul in care facem update
			-> cuv "search" reprezinta update-ul unui anumit camp din tabel, urmat de ce vrem sa facem update respectiv valoarea lui pe urmatoarele 2 pozitii
	*/
}

void Update::executeQuery(std::string query, SQLHANDLE StmtHandle, std::string state, int command)
{
	SQLSMALLINT retcode;

	retcode = SQLFreeStmt(StmtHandle, SQL_CLOSE);
	if (SQL_SUCCESS != retcode)
		throw QueryExecution(query);

	retcode = SQLPrepareA(StmtHandle, (SQLCHAR*)query.c_str(), SQL_NTS);
	if (SQL_SUCCESS != retcode)
		throw QueryExecution(query);

	retcode = SQLExecute(StmtHandle);
	if (SQL_SUCCESS != retcode)
		throw QueryExecution(query);

}
