#include "FactoryQuery.h"
#include "Select.h"
#include "Insert.h"
#include "Update.h"
#include "Delete.h"

IQuery* FactoryQuery::getSelectQuery()
{
	return new Select();
}

IQuery* FactoryQuery::getSelectQuery(std::vector<std::string> parameters)
{
	return new Select(parameters);
}


IQuery* FactoryQuery::getInsertQuery()
{
	return new Insert;
}

IQuery* FactoryQuery::getInsertQuery(std::vector<std::string> parameters)
{
	return new Insert(parameters);
}


IQuery* FactoryQuery::getUpdateQuery()
{
	return new Update;
}

IQuery* FactoryQuery::getUpdateQuery(std::vector<std::string> parameters)
{
	return new Update(parameters);
}


IQuery* FactoryQuery::getDeleteQuery()
{
	return new Delete;
}

IQuery* FactoryQuery::getDeleteQuery(std::vector<std::string> parameters)
{
	return new Delete(parameters);
}