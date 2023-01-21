#pragma once
#include "AbsQuery.h"

class Update :
    public AbsQuery
{
public:
    Update();
    Update(std::vector<std::string> parameters);

    const std::string& getQName() override;
    void setQName(std::string name) override;

    void addPar(std::string par) override;
    virtual std::string createQuery() override;
    void executeQuery(std::string query, SQLHANDLE StmtHandle, std::string state = "", int command = 0) override;
};
