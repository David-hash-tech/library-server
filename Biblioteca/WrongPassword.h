#pragma once
#include "AbsException.h"

class WrongPassword :
    public AbsException
{
public:
    WrongPassword();
    void handleException(int Socket) override;
};

