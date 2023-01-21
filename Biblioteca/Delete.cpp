#include "Delete.h"
#include "QueryCreation.h"
#include "QueryExecution.h"


Delete::Delete() :AbsQuery("Delete")
{
}

Delete::Delete(std::vector<std::string> parameters) : AbsQuery("Delete", parameters)
{

}


const std::string& Delete::getQName()
{
	return this->QName;
}

void Delete::addPar(std::string par)
{
	this->parameters.push_back(par);
}

void Delete::setQName(std::string name)
{
	this->QName = name;
}

std::string Delete::createQuery()
{
	std::string query;

	switch (parameters.size())
	{
	case 2:
		query = "delete from " + parameters[0] + " where ID_" + parameters[0] + "= '" + parameters[1] + "'";
		break;

	case 4:
		if (parameters[1] == "search")
			query = "delete from " + parameters[0] + " where " + parameters[2] + "= '" + parameters[3] + "'";
		break;

	case 7:
		if (parameters[1] == "search" && parameters[4] == "and")
			query = "delete from " + parameters[0] + " where " + parameters[2] + "= '" + parameters[3] + "'" + " and " + parameters[5] + "= '" + parameters[6] + "'";
		break;

	default:
		throw QueryCreation("Delete");
		break;
	}

	return query;
	/*
	in vectorul parameters:
		poz 0 -> tabelul in care facem update
		-> cuv "search" reprezinta delete-ul unei anumite inregistrari din tabel, urmat de ce vrem sa facem delete respectiv valoarea lui pe urmatoarele 2 pozitii
		-> cuv "and" reprezinta adugarea unui al doilea criteriu de delete, urmat de valoarea lui pe pozitia urmatoare
	*/
}

void Delete::executeQuery(std::string query, SQLHANDLE StmtHandle, std::string state, int command)
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
