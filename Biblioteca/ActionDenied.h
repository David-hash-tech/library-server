#pragma once
#include "AbsException.h"
class ActionDenied :
    public AbsException
{
public:
    ActionDenied(int command);
    void handleException(int Socket) override;
};

