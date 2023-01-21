#pragma once
#include <string>
#include <vector>

class IQuery;
class FactoryQuery
{
public:
	static IQuery* getSelectQuery();
	static IQuery* getSelectQuery(std::vector<std::string> parameters);

	static IQuery* getInsertQuery();
	static IQuery* getInsertQuery(std::vector<std::string> parameters);

	static IQuery* getUpdateQuery();
	static IQuery* getUpdateQuery(std::vector<std::string> parameters);

	static IQuery* getDeleteQuery();
	static IQuery* getDeleteQuery(std::vector<std::string> parameters);
};

