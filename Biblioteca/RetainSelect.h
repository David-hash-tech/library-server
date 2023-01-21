#pragma once
#include <string>
#include <vector>

//RETINE DOAR INFORMATIILE DE PE UN RAND!!!

class retainSelect
{
private:
    retainSelect();
    ~retainSelect() { ; };

public:
    std::string msg;
    short Columns = 0;
    std::vector<char*> data;
    std::vector<long> szdata;
    static retainSelect* instance;

    static void destroyInstance();
    static retainSelect& getInstance();

    void zeroize();
    bool ver(int poz, std::string value);
    bool ver(int poz1, std::string value1, int poz2, std::string value2);
};

