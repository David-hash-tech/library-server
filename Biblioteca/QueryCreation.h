#pragma once
#include "AbsException.h"

class QueryCreation :
    public AbsException
{
private:
    std::string querytype;

public:
    QueryCreation(std::string querytype);
    void handleException(int Socket) override;
};

