#include "RetainSelect.h"

retainSelect* retainSelect::instance = nullptr;

retainSelect::retainSelect()
{
    retainSelect::Columns = 12;
    this->szdata.resize(this->Columns);
    for (int i = 0; i < this->Columns; i++)
        this->data.push_back(new char(256));
}

retainSelect& retainSelect::getInstance()
{
    if (retainSelect::instance == nullptr)
    {
        retainSelect::instance = new retainSelect;
    }

    return *retainSelect::instance;
}

void retainSelect::zeroize()
{
    for (int i = 0; i < this->Columns; i++)
    {
        this->data[i][0] = '\0';
        this->szdata[i] = 0;
    }
}

void retainSelect::destroyInstance()
{
    if (retainSelect::instance != nullptr)
    {
        delete retainSelect::instance;
        retainSelect::instance = nullptr;
    }
}

bool retainSelect::ver(int poz, std::string value)
{
    if (this->data.size() <= poz)
        return false;
    if (this->szdata[poz] != 0)
        if (this->data[poz] == value.c_str())
            return true;
    return false;
}

bool retainSelect::ver(int poz1, std::string value1, int poz2, std::string value2)
{
    if (this->data.size() <= poz1 && this->data.size() <= poz2)
        return false;
    if (this->szdata[poz1] != 0 && this->szdata[poz2] != 0)
        if (this->data[poz1] == value1.c_str() && this->data[poz2] == value2.c_str())
            return true;
    return false;
}