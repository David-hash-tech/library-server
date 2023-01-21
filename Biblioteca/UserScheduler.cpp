#include "UserScheduler.h"
#include "IQuery.h"
#include "TipAbonament.h"
#include "RetainSelect.h"
#include "FactoryQuery.h"
#include "FactoryUser.h"
#include "InvalidCommand.h"
#include "WrongLogin.h"
#include "WrongPassword.h"
#include "WrongUsername.h"
#include "SendMsg.h"
#include "Logger.h"


IUser* UserScheduler::instance[5] = { nullptr, };

IUser* UserScheduler::getInstance(int Socket)
{
	for (int i = 0; i < MaxUsers; i++)
		if (UserScheduler::instance[i] != nullptr)
			if (UserScheduler::instance[i]->getSocketID() == Socket)
				return UserScheduler::instance[i];

	return nullptr;
}

IUser* UserScheduler::createInstance(IUser* user)
{
	for (int i = 0; i < MaxUsers; i++)
		if (!UserScheduler::instance[i])
		{
			UserScheduler::instance[i] = user;
			return UserScheduler::instance[i];
		}
	return nullptr;
}

void UserScheduler::destroyInstance(int Socket)
{
	for (int i = 0; i < 5; i++)
		if(UserScheduler::instance[i])
			if (UserScheduler::instance[i]->getSocketID() == Socket)
			{
				delete UserScheduler::instance[i];
				UserScheduler::instance[i] = nullptr;
			}
}


void UserScheduler::login(int Socket, std::vector<std::string> MsgParts)
{
	if (MsgParts.size() != 3)
		throw InvalidCommand(1);

	IQuery* sq = FactoryQuery::getSelectQuery({ "Useri","search","Username", MsgParts[1], "and", "Parola", MsgParts[2] });
	std::string query = sq->createQuery();
	sq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());
	delete sq;
	if (retainSelect::getInstance().szdata[0] == 0)		//daca nu s-a citit nimic inseamna ca nu exista utilizatorul in BD
		throw WrongLogin();

	std::string username = MsgParts[1];
	if (retainSelect::getInstance().szdata[1] == (-1))		//daca nu s-a citit TipAbonament inseamna ca este bibliotecar
	{
		UserScheduler::createInstance(FactoryUser::getBibliotecar(Socket, username, TipAbonament::NoType));
		SendMsg::getInstance()->Send(Socket, { "1/Bibliotecar" });
	}
	else
	{
		UserScheduler::createInstance(FactoryUser::getClient(Socket, username, (TipAbonament)(std::stoi(retainSelect::getInstance().data[1]))));
		SendMsg::getInstance()->Send(Socket, { "1/Client" });
	}

	Logger::getInstance()->showMsg("Utilizatorul cu username-ul " + username + " s-a logat cu succes!");
}

void UserScheduler::inregistrare(int Socket, std::vector<std::string> MsgParts)
{
	if (MsgParts.size() != 12)
		throw InvalidCommand(2);

	if (MsgParts[3].rfind("/") != std::string::npos)	//username-ul contine caracterul '/'
		throw WrongUsername(MsgParts[3]);

	if (MsgParts[4] != MsgParts[5])	//confirmarea parolei nu este identica cu parola
		throw WrongPassword();


	IQuery* sq = FactoryQuery::getSelectQuery({ "Useri","search","Username",MsgParts[3] });
	std::string query = sq->createQuery();
	sq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle(), "verify");
	delete sq;

	std::vector<std::string> p;
	p = { "Useri","into","IDAbonament","IDTipUser","Username","Parola","Nume","Prenume","Ocupatie","CNP","Email","Telefon","values" };
	for (int i = 1; i < MsgParts.size(); i++)
		if (i != 5)
			p.push_back(MsgParts[i]);

	IQuery* iq = FactoryQuery::getInsertQuery(p);
	query = iq->createQuery();
	iq->executeQuery(query, DataBaseConn::getInstance()->getStmtHandle());

	delete iq;

	SendMsg::getInstance()->getInstance()->Send(Socket, { "2/Succeded" });
	Logger::getInstance()->showMsg("A fost inregistrat un nou utilizator cu username-ul " + (std::string)retainSelect::getInstance().data[3] + "!");
}
