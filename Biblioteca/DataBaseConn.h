#pragma once
#include <string>
#include <wtypes.h>
#include <sqlext.h>

#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

class DataBaseConn
{
private:
    SQLHANDLE sqlEnvHandle;
    SQLHANDLE sqlStmtHandle = NULL;
    SQLHANDLE sqlConnHandle = NULL;

    SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];

    std::wstring DBName;
    static DataBaseConn* instance;

    DataBaseConn(std::wstring DBName);
    ~DataBaseConn() { ; }
    void connect();

public:
    static DataBaseConn* getInstance();
    static DataBaseConn* createInstance(std::wstring DBName);
    static void destroyInstance();
    
    const std::wstring& getName();
    void setName(std::wstring DBName);

    const SQLHANDLE& getConnHandle();
    const SQLHANDLE& getStmtHandle();
    const SQLHANDLE& getEnvHandle();

    void disconnect();
};

