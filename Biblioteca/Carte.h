#pragma once
#include "AbsArticol.h"
class Carte :
    public AbsArticol
{
public:
    Carte(std::string nume, TipArticol art);

	void descarca() override;
	void afiseazaDetalii() override;
	void rezerva(std::string username) override;
	void returneaza(std::string username) override;

	void eliminaArticol() override;
	void adaugaArticol(std::vector<std::string> parameters) override;
	void modificaArticol(std::vector<std::string> parameters) override;
};

