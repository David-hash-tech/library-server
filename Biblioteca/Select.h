#pragma once
#include "AbsQuery.h"

class Select :
    public AbsQuery
{
public:
    Select();
    Select(std::vector<std::string> parameters);

    const std::string& getQName() override;
    void setQName(std::string name) override;

    std::string createQuery() override;
    void addPar(std::string par) override;
    void executeQuery(std::string query, SQLHANDLE StmtHandle, std::string state = "", int command = 0) override;
};

