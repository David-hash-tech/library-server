#pragma once
#include <iostream>
#include "IArticol.h"
#include "TipArticol.h"

class AbsArticol :
    public IArticol
{
protected:
    TipArticol art;
    std::string name;

public:
    AbsArticol(std::string name, TipArticol art);

};
