#include "Carte.h"
#include "IQuery.h"
#include "FactoryQuery.h"
#include "RetainSelect.h"
#include "NotEnoughBooks.h"


Carte::Carte(std::string nume, TipArticol art):AbsArticol(nume, art)
{
}

int getNrBooks(std::string carte)
{
	IQuery* sq = FactoryQuery::getSelectQuery({ "Carte","search", "Nume",carte,"just","Exemplare" });
	std::string query = sq->createQuery();
	sq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete sq;

	return std::stoi(retainSelect::getInstance().data[0]);
}


void Carte::afiseazaDetalii()
{
	IQuery* sq = FactoryQuery::getSelectQuery({ "Carte","search","Nume",this->name });
	std::string query = sq->createQuery();
	sq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete sq;

	std::string msg = "10";
	for (int i = 1; i < retainSelect::getInstance().Columns - 1; i++)
		msg = msg + "/" + (std::string)retainSelect::getInstance().data[i];

	retainSelect::getInstance().msg = msg;
}

void Carte::descarca()
{
	IQuery* sq = FactoryQuery::getSelectQuery({ "Carte","search","Nume",this->name,"just","PDF" });
	std::string query = sq->createQuery();
	sq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete sq;
}

void Carte::rezerva(std::string username)
{
	std::string query;

	int exemplare = getNrBooks(this->name);
	if (exemplare == 0)
		throw NotEnoughBooks(this->name);

	IQuery* iq = FactoryQuery::getInsertQuery({ "Imprumut", "into", "Username", "Carte", "values", username, this->name });
	query = iq->createQuery();
	iq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete iq;

	IQuery* uq = FactoryQuery::getUpdateQuery({ "Carte", "Exemplare", std::to_string(--exemplare), "search", "Nume", this->name });
	query = uq->createQuery();
	uq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete uq;
}

void Carte::returneaza(std::string username)
{
	std::string query;

	IQuery* dq = FactoryQuery::getDeleteQuery({ "Imprumut", "search", "Username", username, "and", "Carte", this->name });
	query = dq->createQuery();
	dq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete dq;

	int exemplare = getNrBooks(this->name);

	IQuery* uq = FactoryQuery::getUpdateQuery({ "Carte", "Exemplare", std::to_string(++exemplare), "search", "Nume", this->name });
	query = uq->createQuery();
	uq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete uq;
}


void Carte::modificaArticol(std::vector<std::string> parameters)
{
	std::string query;

	for (int i = 2; i < parameters.size(); i += 2)
	{
		IQuery* uq = FactoryQuery::getUpdateQuery({ "Carte",parameters[i],parameters[i + 1],"search","Nume",parameters[1] });
		query = uq->createQuery();
		uq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
		delete uq;
	}
}

void Carte::eliminaArticol()
{
	std::string query;

	IQuery* dq1 = FactoryQuery::getDeleteQuery({ "Carte", "search","Nume",this->name });
	query = dq1->createQuery();
	dq1->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete dq1;

	IQuery* dq2 = FactoryQuery::getDeleteQuery({ "ListaArticole", "search", "Nume", this->name });
	query = dq2->createQuery();
	dq2->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete dq2;
}

void Carte::adaugaArticol(std::vector<std::string> parameters)
{
	std::string query;

	IQuery* iq = FactoryQuery::getInsertQuery({ "Carte", "into", "IDAbonament", "Nume", "Autor", "DataPublicare", "Editura",
		"NrPagini", "Exemplare", "Descriere", "Imagine", "PDF", "values",parameters[2], parameters[3], parameters[4], parameters[5],
		parameters[6], parameters[7],parameters[8], parameters[9], parameters[10], parameters[11] });
	query = iq->createQuery();
	iq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete iq;

	IQuery* iq1 = FactoryQuery::getInsertQuery({ "ListaArticole", "into", "Nume", "TipArticol", "values", parameters[3], std::to_string((int)TipArticol::Carte) });
	query = iq1->createQuery();
	iq1->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete iq1;
}
