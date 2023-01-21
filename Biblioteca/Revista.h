#pragma once
#include "AbsArticol.h"
#include "ActionDenied.h"

class Revista :
    public AbsArticol
{
public:
    Revista(std::string nume, TipArticol art);

	void descarca() override;
	void afiseazaDetalii() override;
	void rezerva(std::string username) override { throw ActionDenied(11); };
	void returneaza(std::string username) override { throw ActionDenied(12); };
	
	void eliminaArticol() override;
	void adaugaArticol(std::vector<std::string> parameters) override;
	void modificaArticol(std::vector<std::string> parameters) override;
};

