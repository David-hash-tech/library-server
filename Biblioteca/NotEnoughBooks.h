#pragma once
#include "AbsException.h"
class NotEnoughBooks :
    public AbsException
{
private:
    std::string carte;

public:
    NotEnoughBooks(std::string carte);
    void handleException(int Socket) override;
};

