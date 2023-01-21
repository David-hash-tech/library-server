#include "AbsUser.h"
#include <iostream>
#include <fstream>
#include "IQuery.h"
#include "IArticol.h"
#include "FactoryArticol.h"
#include "RetainSelect.h"
#include "FactoryQuery.h"
#include "FactoryUser.h"
#include "SendMsg.h"
#include "Logger.h"


AbsUser::AbsUser()
{
}

AbsUser::AbsUser(int Socket, std::string username, TipAbonament Ab)
{
	this->Ab = Ab;
	this->username = username;
	this->Socket = Socket;
}


void AbsUser::cauta(std::string secventa)
{
	std::string query;

	IQuery* sq1 = FactoryQuery::getSelectQuery({ "Carte", "search", "Nume", "like", secventa, "just", "Nume", "and", "IDAbonament", std::to_string((int)this->Ab) });
	query = sq1->createQuery();
	sq1->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle(), "show", 9);
	delete sq1;
	std::string msg = retainSelect::getInstance().msg;


	IQuery* sq2 = FactoryQuery::getSelectQuery({ "Revista", "search", "Nume", "like", secventa, "just", "Nume", "and", "IDAbonament", std::to_string((int)this->Ab) });
	query = sq2->createQuery();
	sq2->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle(), "show");
	delete sq2;
	msg = msg + retainSelect::getInstance().msg;


	IQuery* sq3 = FactoryQuery::getSelectQuery({ "Ziar", "search", "Nume", "like", secventa, "just", "Nume", "and", "IDAbonament", std::to_string((int)this->Ab) });
	query = sq3->createQuery();
	sq3->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle(), "show");
	delete sq3;
	msg = msg + retainSelect::getInstance().msg;

	SendMsg::getInstance()->Send(Socket, { msg });
	Logger::getInstance()->showMsg("Utilizatorul " + this->username + " a cautat secventa \"" + secventa + "\"!");
}

void AbsUser::afiseazaDetaliiArticol(std::string articol)
{
	IArticol* art = FactoryArticol::getArticol(articol);
	art->afiseazaDetalii();
	delete art;

	SendMsg::getInstance()->Send(Socket, { retainSelect::getInstance().msg });
	Logger::getInstance()->showMsg("Utilizatorul " + this->username + " a afisat detalii despre articolul " + articol);
}

void AbsUser::descarcaArticol(std::string articol)
{
	IArticol* art = FactoryArticol::getArticol(articol);
	art->descarca();
	delete art;

	SendMsg::getInstance()->Send(Socket, { "12/", retainSelect::getInstance().data[0] });
	Logger::getInstance()->showMsg("Utilizatorul " + this->username + " a descarcat articolul " + articol);
}

void AbsUser::afisareProfil()
{
	IQuery* sq = FactoryQuery::getSelectQuery({ "Useri","search","Username",this->username });
	std::string query = sq->createQuery();
	sq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete sq;

	SendMsg::getInstance()->Send(this->Socket, { "3", retainSelect::getInstance().data[1],retainSelect::getInstance().data[3],
		retainSelect::getInstance().data[5], retainSelect::getInstance().data[6], retainSelect::getInstance().data[7], 
		retainSelect::getInstance().data[8], retainSelect::getInstance().data[9],retainSelect::getInstance().data[10] });
	Logger::getInstance()->showMsg("A fost afisat profilul utilizatorului " + this->username);
}

void AbsUser::afisareProgram()
{
	std::string msg, aux;
	std::ifstream f("Program.txt");

	if (f.is_open())
	{
		while (std::getline(f, aux))
			msg = msg + aux + "\n";
	}
	f.close();

	SendMsg::getInstance()->Send(this->Socket, { msg });
	Logger::getInstance()->showMsg("Utilizatorul " + this->username + " a afisat programul bibliotecii!");
}

void AbsUser::afisareContact()
{
	std::string msg, aux;
	std::ifstream f("Contact.txt");

	if (f.is_open())
	{
		while (std::getline(f, aux))
			msg = msg + aux + "\n";
	}
	f.close();

	SendMsg::getInstance()->Send(this->Socket, { msg });
	Logger::getInstance()->showMsg("Utilizatorul " + this->username + " a afisat datele de contact ale bibliotecii!");
}

void AbsUser::deconectare()
{
	SendMsg::getInstance()->Send(this->Socket, { "Deconectare cu succes!" });
	Logger::getInstance()->showMsg("Utilizatorul " + this->username + " s-a deconectat cu succes!");
}


void AbsUser::schimbaParola(std::string newPassword)
{
	IQuery* uq = FactoryQuery::getUpdateQuery({ "Useri","Parola",newPassword, "search", "Username", this->username });
	std::string query = uq->createQuery();
	uq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete uq;

	SendMsg::getInstance()->Send(this->Socket, { "6/Succeded" });
	Logger::getInstance()->showMsg("Utilizatorul " + this->username + " si-a schimbat parola!");
}

void AbsUser::schimbaEmail(std::string newEmail)
{
	IQuery* uq = FactoryQuery::getUpdateQuery({ "Useri","Email",newEmail, "search", "Username", this->username });
	std::string query = uq->createQuery();
	uq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete uq;

	SendMsg::getInstance()->Send(this->Socket, { "7/Succeded" });
	Logger::getInstance()->showMsg("Utilizatorul " + this->username + " si-a schimbat email-ul!");
}

void AbsUser::schimbaTelefon(std::string newTelefon)
{
	IQuery* uq = FactoryQuery::getUpdateQuery({ "Useri","Telefon",newTelefon, "search", "Username", this->username });
	std::string query = uq->createQuery();
	uq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete uq;

	SendMsg::getInstance()->Send(this->Socket, { "8/Succeded" });
	Logger::getInstance()->showMsg("Utilizatorul " + this->username + " si-a schimbat numarul de telefon!");
}
