#include "Imprumut.h"
#include "FactoryQuery.h"
#include "IQuery.h"

Imprumut::Imprumut(std::string username) :username(username)
{

}


void Imprumut::prelungireTermen(std::string numeCarte)
{
	IQuery* uq = FactoryQuery::getUpdateQuery({ "Imprumut","DataRetur","7","search","Username",this->username,"and","Carte",numeCarte });
	std::string query = uq->createQuery();
	uq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete uq;
}

void Imprumut::afisareCartiImprumutate(int command)
{
	IQuery* sq = FactoryQuery::getSelectQuery({ "Imprumut","search","Username",this->username });
	std::string query = sq->createQuery();
	sq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle(), "show", command);
	delete sq;
}


void Imprumut::afiseazaImprumuturiExp_B()
{
	IQuery* sq = FactoryQuery::getSelectQuery({ "Imprumut" });
	std::string query = sq->createQuery();
	sq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle(), "show", 15);
	delete sq;
}
