#include "AbsQuery.h"
#include <codecvt>

AbsQuery::AbsQuery(std::string qname) :AbsQuery(qname, {})
{
	
}

AbsQuery::AbsQuery(std::string qname, std::vector<std::string> par)
	:QName(qname),parameters(par)
{
	
}
