#include "FactoryArticol.h"
#include "IQuery.h"
#include "RetainSelect.h"
#include "FactoryQuery.h"
#include "Carte.h"
#include "Ziar.h"
#include "Revista.h"
#include "TipArticol.h"

IArticol* FactoryArticol::getArticol(std::string numeCarte)
{
	IQuery* sq = FactoryQuery::getSelectQuery({ "ListaArticole","search", "Nume", numeCarte, "just", "TipArticol" });
	std::string query = sq->createQuery();
	sq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());

	int TipArticol = std::stoi(retainSelect::getInstance().data[0]);
	switch (TipArticol)
	{
	case (int)(TipArticol::Carte):
		return new Carte(numeCarte, TipArticol::Carte);
		break;

	case (int)(TipArticol::Revista):
		return new Revista(numeCarte,TipArticol::Revista);
		break;

	case (int)(TipArticol::Ziar):
		return new Ziar(numeCarte, TipArticol::Ziar);

	default:
		return nullptr;
	}
}

IArticol* FactoryArticol::createArticol(std::string nume, TipArticol type)
{
	if (type == TipArticol::Carte)
		return new Carte(nume, type);

	if (type == TipArticol::Revista)
		return new Revista(nume, type);

	if (type == TipArticol::Ziar)
		return new Ziar(nume, type);
}
