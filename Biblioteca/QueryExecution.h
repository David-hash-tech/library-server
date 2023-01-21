#pragma once
#include "AbsException.h"

class QueryExecution :
    public AbsException
{
private:
    std::string query;

public:
    QueryExecution(std::string query);
    void handleException(int Socket) override;
};

