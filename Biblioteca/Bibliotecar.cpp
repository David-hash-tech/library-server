#include "Bibliotecar.h"
#include "Imprumut.h"
#include "SendMsg.h"
#include "Logger.h"
#include "IArticol.h"
#include "FactoryArticol.h"
#include "InvalidCommand.h"
#include "RetainSelect.h"


Bibliotecar::Bibliotecar()
{

}

Bibliotecar::Bibliotecar(int Socket, std::string username, TipAbonament Ab):AbsUser(Socket, username, Ab)
{

}


void Bibliotecar::afiseazaImprumuturiExp_B()
{
	Imprumut i(this->username);
	i.afiseazaImprumuturiExp_B();

	SendMsg::getInstance()->Send(this->Socket, { retainSelect::getInstance().msg });
	Logger::getInstance()->showMsg("Au fost afisate toate cartile imprumutate. Bibliotecar: " + this->username);
}

void Bibliotecar::adaugaArticol_B(std::vector<std::string> parameters)
{
	if (parameters.size() != 12 && parameters.size() != 8 && parameters.size() != 6)
		throw InvalidCommand(14);

	IArticol* art = FactoryArticol::createArticol(parameters[3], (TipArticol)(std::stoi(parameters[1])));
	art->adaugaArticol(parameters);
	delete art;

	SendMsg::getInstance()->Send(this->Socket, { "14/Succeded" });
	Logger::getInstance()->showMsg("Bibliotecarul " + this->username + " a adaugat articolul " + parameters[3] + " cu toate detaliile aferente");
}

void Bibliotecar::modificaArticol_B(std::vector<std::string> parameters)
{
	if (((parameters.size() - 2) / 2) % 2 == 1)
		throw InvalidCommand(16);

	IArticol* art = FactoryArticol::getArticol(parameters[1]);
	art->modificaArticol(parameters);
	delete art;

	SendMsg::getInstance()->Send(this->Socket, { "16/Succeded" });
	Logger::getInstance()->showMsg("Bibliotecarul " + this->username + " a modificat detalii ale articolului " + parameters[1]);
}

void Bibliotecar::eliminaArticol_B(std::string carte)
{
	IArticol* art = FactoryArticol::getArticol(carte);
	art->eliminaArticol();
	delete art;

	SendMsg::getInstance()->Send(this->Socket, { "17/Succeded" });
	Logger::getInstance()->showMsg("Bibliotecarul " + this->username + " a eliminat articolul " + carte);
}
