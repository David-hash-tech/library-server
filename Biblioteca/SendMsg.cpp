#define _CRT_SECURE_NO_WARNINGS
#include "SendMsg.h"
#include <winSock2.h>

SendMsg* SendMsg::instance = nullptr;

SendMsg* SendMsg::getInstance()
{
    if (instance == nullptr)
        instance = new SendMsg();

    return instance;
}

void SendMsg::destroyInstance()
{
    if (instance == nullptr)
        return;

    delete instance;
    instance = nullptr;
}

void SendMsg::Send(int Socket, std::vector<std::string> parameters)
{
    strcpy(this->MsgToClient, parameters[0].c_str());
    for (int i = 1; i < parameters.size(); i++)
    {
        strcat(this->MsgToClient, "/");
        strcat(this->MsgToClient, parameters[i].c_str());
    }

    send(Socket, this->MsgToClient, strlen(this->MsgToClient) + 1, 0);
}
