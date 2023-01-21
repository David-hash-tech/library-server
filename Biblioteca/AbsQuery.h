#pragma once
#include <vector>
#include "IQuery.h"

class AbsQuery :
    public IQuery
{
protected:
    std::string QName;
    std::vector<std::string> parameters;

public:
    AbsQuery(std::string qname);
    AbsQuery(std::string qname, std::vector<std::string> par);

};

