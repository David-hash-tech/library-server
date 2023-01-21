#include "DataBaseConn.h"
#include "Logger.h"
#include <iostream>

DataBaseConn* DataBaseConn::instance = nullptr;

DataBaseConn::DataBaseConn(std::wstring name):DBName(name)
{
    connect();
}

DataBaseConn* DataBaseConn::createInstance(std::wstring name)
{
    if (instance == nullptr)
        instance = new DataBaseConn(name);

    return instance;
}

DataBaseConn* DataBaseConn::getInstance()
{
    return instance;
}

void DataBaseConn::destroyInstance()
{
    if (instance == nullptr)
        return;

    instance->disconnect();
    delete instance;
    instance = nullptr;
}

void DataBaseConn::setName(std::wstring name)
{
    if (this->DBName != name)
    {
        this->DBName = name;
        connect();
    }
}

const std::wstring& DataBaseConn::getName() 
{
    return DBName;
}

const SQLHANDLE& DataBaseConn::getConnHandle()
{
    return this->sqlConnHandle;
}

const SQLHANDLE& DataBaseConn::getStmtHandle()
{
    return this->sqlStmtHandle;
}

const SQLHANDLE& DataBaseConn::getEnvHandle()
{
    return this->sqlEnvHandle;
}

void DataBaseConn::connect()
{
    //allocations
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
        disconnect();

    if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        disconnect();

    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
        disconnect();

    //output
    Logger::getInstance()->showMsg("Attempting connection to SQL Server...");

    std::wstring p = L"DRIVER={SQL Server};SERVER=DESKTOP-OCPUGRE, 1434;DATABASE=";
    p.append(this->DBName);
    p.append(L"; Trusted = true;");

    switch (SQLDriverConnect(sqlConnHandle, NULL, (SQLWCHAR*)p.c_str(), SQL_NTS, retconstring, 1024, NULL, SQL_DRIVER_NOPROMPT))
    {
    case SQL_SUCCESS:
        Logger::getInstance()->showMsg("Successfully connected to SQL Server");
        break;

    case SQL_SUCCESS_WITH_INFO:
        Logger::getInstance()->showMsg("Successfully connected to SQL Server");
        break;

    case SQL_INVALID_HANDLE:
        Logger::getInstance()->showMsg("Could not connect to SQL Server");
        disconnect();
        break;

    case SQL_ERROR:
        Logger::getInstance()->showMsg("Could not connect to SQL Server");
        disconnect();
        break;

    default:
        break;
    }

    //if there is a problem connecting then exit application
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
        disconnect();
}

void DataBaseConn::disconnect()
{
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    SQLDisconnect(sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
}
