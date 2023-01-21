#include "FactoryUser.h"
#include "Client.h"
#include "Bibliotecar.h"

IUser* FactoryUser::getClient()
{
	return new Client;
}

IUser* FactoryUser::getClient(int Socket, std::string username, TipAbonament Ab)
{
	return new Client(Socket, username, Ab);
}


IUser* FactoryUser::getBibliotecar()
{
	return new Bibliotecar();
}

IUser* FactoryUser::getBibliotecar(int Socket, std::string username, TipAbonament Ab)
{
	return new Bibliotecar(Socket, username, Ab);
}
