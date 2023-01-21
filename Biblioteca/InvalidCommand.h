#pragma once
#include "AbsException.h"

class InvalidCommand :
    public AbsException
{
public:
    InvalidCommand(int command);
    void handleException(int Socket) override;
};

