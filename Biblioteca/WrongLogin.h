#pragma once
#include "AbsException.h"

class WrongLogin :
    public AbsException
{
public:
    WrongLogin();
    void handleException(int Socket) override;
};

