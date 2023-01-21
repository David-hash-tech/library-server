#pragma once
#include "AbsArticol.h"
#include "ActionDenied.h"

class Ziar :
    public AbsArticol
{
public:
    Ziar(std::string nume, TipArticol art);
    
	void descarca() override;
	void afiseazaDetalii() override;
	void rezerva(std::string username) override { throw ActionDenied(11); };
	void returneaza(std::string username) override { throw ActionDenied(12); };
	

	void eliminaArticol() override;
	void adaugaArticol(std::vector<std::string> parameters) override;
	void modificaArticol(std::vector<std::string> parameters) override;
};
