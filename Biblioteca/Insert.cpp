#include <iostream>
#include "Insert.h"
#include "QueryCreation.h"
#include "QueryExecution.h"

Insert::Insert() :AbsQuery("Insert")
{
}

Insert::Insert(std::vector<std::string> par) : AbsQuery("Insert", par)
{

}


void Insert::setQName(std::string Qname)
{
	this->QName = Qname;
}

const std::string& Insert::getQName()
{
	return this->QName;
}


void Insert::addPar(std::string par)
{
	this->parameters.push_back(par);
}

std::string Insert::createQuery()
{
	std::string query;
	if (parameters[1] == "into")
	{
		int i;
		query = "insert into " + parameters[0] + " (";

		for (i = 2; parameters[i + 1] != "values"; i++)
			query = query + parameters[i] + ",";
		query = query + parameters[i++] + ") ";

		if (i - 2 != parameters.size() - i - 1)
			throw QueryCreation("Insert");
		else
		{
			query = query + parameters[i++] + " (";

			for (; i < parameters.size() - 1; i++)
			{
				query = query + "'" + parameters[i] + "', ";
			}
			query = query + "'" + parameters[i] + "'" + ")";
		}
	}

	return query;
	/*
	in vectorul parameters:
		poz 0 -> tabelul in care inseram
				-> cuv "into" reprezinta inceperea secventei de coloane in care vrem sa introdeucem date
				-> cuv "values" reprezinta sfarsitul secventei de coloane si inceperea sirului de date de introdus
	*/
}

void Insert::executeQuery(std::string query, SQLHANDLE StmtHandle, std::string state, int command)
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
