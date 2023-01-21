#include "Select.h"
#include "QueryCreation.h"
#include "QueryExecution.h"
#include "UniqueUsername.h"
#include "RetainSelect.h"


Select::Select() :AbsQuery("Select")
{

}

Select::Select(std::vector<std::string> parameters) :AbsQuery("select", parameters)
{

}


void Select::setQName(std::string Qname)
{
	this->QName = Qname;
}

const std::string& Select::getQName()
{
	return this->QName;
}


void Select::addPar(std::string par)
{
    this->parameters.push_back(par);
}

std::string Select::createQuery()
{
    std::string query;

    switch (parameters.size())
    {
    case 1:
        query = "select * from " + parameters[0];
        break;

    case 2:
        query = "select * from " + parameters[0] + " where ID_" + parameters[0] + " = '" + parameters[1] + "'";
        break;

    case 4:
        if (parameters[1] == "search")
            query = "select * from " + parameters[0] + " where " + parameters[2] + " ='" + parameters[3] + "'";

        if (parameters[1] == "just")
            query = "select " + parameters[2] + " from " + parameters[0] + " where ID_" + parameters[0] + " = '" + parameters[3] + "'";

        break;

    case 6:
        if (parameters[1] == "search" && parameters[4] == "just")
            query = "select " + parameters[5] + " from " + parameters[0] + " where " + parameters[2] + " ='" + parameters[3] + "'";
        break;

    case 7:
        if (parameters[1] == "search" && parameters[4] == "and")
            query = "select * from " + parameters[0] + " where " + parameters[2] + " ='" + parameters[3] + "' and " + parameters[5] + " ='" + parameters[6] + "'";
        
        break;

    case 8:
        if (parameters[1] == "search" && parameters[4] == "just" && parameters[6] == "and")
            query = "select " + parameters[5] + "," + parameters[7] + " from " + parameters[0] + " where " + parameters[2] + " = '" + parameters[3] + "' ";
        break;

    case 10:
        if (parameters[1] == "search" && parameters[3] == "like" && parameters[5] == "just" && parameters[7] == "and")
            query = "select " + parameters[6] + " from " + parameters[0] + " where (" + parameters[2] + " like '" + parameters[4] + "%' or " + parameters[2] + " like '% " + parameters[4] + "%') and " + parameters[8] + " ='" + parameters[9] + "'";
        break;

    default:
        throw QueryCreation("select");
        break;
    }

    return query;
    /*
    in vectorul parameters:
        poz 0 -> tabelul in care cautam
        -> cuv "search" reprezinta selectia unui anumit camp din tabel, urmat de ce vrem sa cautam respectiv valoarea lui pe urmatoarele 2 pozitii
        -> cuv "just" reprezinta selectia unui singur camp din tabel, urmat de valoarea lui pe pozitia urmatoare
        -> cuv "and" reprezinta -selectia unui al doilea camp din tabel, urmat de valoarea lui pe pozitia urmatoare, daca apare si "just"
                                -adugarea unui al doilea criteriu de delete, urmat de valoarea lui pe pozitia urmatoare, daca nu apare "just"
        -> cuv "search", "just", "and" pot aparea in vectoar DOAR in ordinea aceasta;
    */
}

void Select::executeQuery(std::string query, SQLHANDLE StmtHandle, std::string state, int command)
{
    SQLSMALLINT retcode;
    retcode = SQLFreeStmt(StmtHandle, SQL_CLOSE);
    if (SQL_SUCCESS != retcode)
        throw QueryExecution(query);

    retcode = SQLPrepareA(StmtHandle, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (SQL_SUCCESS != retcode)
        throw QueryExecution(query);

    retcode = SQLNumResultCols(StmtHandle, &(retainSelect::getInstance().Columns));
    if (SQL_SUCCESS != retcode)
        throw QueryExecution(query);
    retainSelect::getInstance().zeroize();

    for (int i = 0; i < retainSelect::getInstance().Columns; i++)
        SQLBindCol(StmtHandle, i + 1, SQL_CHAR, retainSelect::getInstance().data[i], 250, &(retainSelect::getInstance().szdata[i]));
 
    retcode = SQLExecute(StmtHandle);
    if (SQL_SUCCESS != retcode)
        throw QueryExecution(query);

    std::string msg;
    if (command != 0)
        msg = std::to_string(command);       //for "show" state

    for (int i = 0; ; i++)
    {
        retcode = SQLFetch(StmtHandle);
        if (retcode != SQL_SUCCESS && retcode != SQL_NO_DATA)
            throw QueryExecution(query);
        if (retcode == SQL_NO_DATA)
            break;
        else
        {
            if (state.compare("verify") == 0)
            {
                if (retainSelect::getInstance().szdata[0] != 0)
                {
                    while (retcode != SQL_NO_DATA)
                        retcode = SQLFetch(StmtHandle);
                    throw UniqueUsername(retainSelect::getInstance().data[3]);
                }
            }
            if (state.compare("show") == 0)
            {
                for (int j = 0; j < retainSelect::getInstance().Columns; j++)
                    msg = msg + "/" + retainSelect::getInstance().data[j];
            }
        }
    }
    
    if (msg.size() == 1 || msg.size() == 2)
        msg = msg + "/";
    retainSelect::getInstance().msg = msg;
    SQLFreeStmt(StmtHandle, SQL_UNBIND);
}
