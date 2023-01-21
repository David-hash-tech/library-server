#pragma once
#include "IException.h"
#include <string>

class AbsException :
    public IException
{
protected:
    int command;
    std::string msg;

public:
    AbsException() { ; };
    AbsException(int command, std::string msg);
};

