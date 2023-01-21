#include "Logger.h"
#include <iostream>

Logger* Logger::instance = nullptr;

Logger* Logger::getInstance()
{
    if (instance == nullptr)
        instance = new Logger();

    return instance;
}

void Logger::destroyInstance()
{
    if (instance == nullptr)
        return;

    delete instance;
    instance = nullptr;
}

void Logger::showMsg(std::string msg)
{
    std::cout << msg << std::endl;
}