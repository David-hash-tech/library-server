#include "Ziar.h"
#include "IQuery.h"
#include "FactoryQuery.h"
#include "RetainSelect.h"


Ziar::Ziar(std::string nume, TipArticol art) :AbsArticol(nume, art)
{
}


void Ziar::afiseazaDetalii()
{
	IQuery* sq = FactoryQuery::getSelectQuery({ "Ziar","search","Nume",this->name });
	std::string query = sq->createQuery();
	sq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete sq;

	std::string msg = "10";
	for (int i = 1; i < retainSelect::getInstance().Columns - 1; i++)
		msg = msg + "/" + (std::string)retainSelect::getInstance().data[i];

	retainSelect::getInstance().msg = msg;
}

void Ziar::descarca()
{
	IQuery* sq = FactoryQuery::getSelectQuery({ "Ziar","search","Nume",this->name,"just","PDF" });
	std::string query = sq->createQuery();
	sq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete sq;
}


void Ziar::adaugaArticol(std::vector<std::string> parameters)
{
	std::string query;
	
	IQuery* iq = FactoryQuery::getInsertQuery({ "Ziar", "into", "IDAbonament", "Nume", "DataTiparire", "PDF", "values",parameters[2],
		parameters[3], parameters[4], parameters[5]});
	query = iq->createQuery();
	iq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete iq;

	IQuery* iq1 = FactoryQuery::getInsertQuery({ "ListaArticole", "into", "Nume", "TipArticol", "values", parameters[3], std::to_string((int)TipArticol::Ziar) });
	query = iq1->createQuery();
	iq1->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete iq1;
}

void Ziar::modificaArticol(std::vector<std::string> parameters)
{
	std::string query;

	for (int i = 2; i < parameters.size(); i += 2)
	{
		IQuery* uq = FactoryQuery::getUpdateQuery({ "Ziar", parameters[i], parameters[i + 1], "search", "Nume", parameters[1] });
		query = uq->createQuery();
		uq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
		delete uq;
	}
}

void Ziar::eliminaArticol()
{
	std::string query;

	IQuery* dq1 = FactoryQuery::getDeleteQuery({ "Ziar", "search", "Nume", this->name });
	query = dq1->createQuery();
	dq1->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete dq1;

	IQuery* dq2 = FactoryQuery::getDeleteQuery({ "ListaArticole", "search", "Nume", this->name });
	query = dq2->createQuery();
	dq2->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete dq2;
}
