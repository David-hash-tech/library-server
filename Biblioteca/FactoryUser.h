#pragma once
#include <string>

enum class TipAbonament;
class IUser;
class FactoryUser
{
public:
	static IUser* getClient();
	static IUser* getClient(int Socket, std::string username, TipAbonament Ab);

	static IUser* getBibliotecar();
	static IUser* getBibliotecar(int Socket, std::string username, TipAbonament Ab);
};
