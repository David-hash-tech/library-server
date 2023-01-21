#include "Client.h"
#include "Imprumut.h"
#include "SendMsg.h"
#include "Logger.h"
#include "IArticol.h"
#include "FactoryArticol.h"
#include "IQuery.h"
#include "FactoryQuery.h"
#include "RetainSelect.h"


Client::Client()
{

}

Client::Client(int Socket, std::string username, TipAbonament Ab):AbsUser(Socket, username, Ab)
{

}


void Client::rezervaCarte(std::string carte)
{
	//TO DO:
	//	verifica daca mai sunt exemplare
	//	verifica daca utilizatorul are abonamentul bun??? -> se poate imprumuta doar dupa cautare, iar cautarea ofera doar carti 
	//															din abonamentul userului
	//	insert query in tabelul Imprumut cu noul imprumut
	//	update query in tabelul Carte in care decrementam numarul de exemplare

	IArticol* art = FactoryArticol::getArticol(carte);
	art->rezerva(this->username);
	delete art;

	SendMsg::getInstance()->Send(this->Socket, { "11/Succeded" });
	Logger::getInstance()->showMsg("Utilizatorul " + this->username + " a imprumutat cartea \"" + carte + "\"!");
}

void Client::returneazaCarte(std::string Carte)
{
	IArticol* art = FactoryArticol::getArticol(Carte);
	art->returneaza(this->username);
	delete art;

	SendMsg::getInstance()->Send(this->Socket, { "12/Succeded" });
	Logger::getInstance()->showMsg("Utilizatorul " + this->username + " a returnat cartea " + Carte);
}

void Client::afisareCartiImprumutate()
{
	Imprumut i(this->username);
	i.afisareCartiImprumutate(4);

	SendMsg::getInstance()->Send(this->Socket, { retainSelect::getInstance().msg });
	Logger::getInstance()->showMsg("Au fost afisate cartile imprumutate de utilizatorul " + this->username);
}

void Client::prelungireTermen(std::string numeCarte)
{
	Imprumut i(this->username);
	i.prelungireTermen(numeCarte);

	SendMsg::getInstance()->Send(this->Socket, { "5/Succeded" });
	Logger::getInstance()->showMsg("A fost prelungit termenul de retur al cartii " + numeCarte + " imprumutata de utilizatorul " + this->username);
}
