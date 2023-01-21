#pragma once
#include <string>
#include <vector>

class IArticol
{
public:
	virtual void descarca() = 0;
	virtual void afiseazaDetalii() = 0;
	virtual void rezerva(std::string username) = 0;
	virtual void returneaza(std::string username) = 0;


	virtual void eliminaArticol() = 0;
	virtual void adaugaArticol(std::vector<std::string> parameters) = 0;
	virtual void modificaArticol(std::vector<std::string> parameters) = 0;
};