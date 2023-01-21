#pragma once
#include "AbsUser.h"
#include "ActionDenied.h"

class Bibliotecar :
    public AbsUser
{
private:

public:
	Bibliotecar();
	Bibliotecar(int Socket, std::string username, TipAbonament Ab);


	void afiseazaImprumuturiExp_B() override;
	void eliminaArticol_B(std::string articol) override;
	void adaugaArticol_B(std::vector<std::string> parameters) override;
	void modificaArticol_B(std::vector<std::string> parameters) override;


	void afisareCartiImprumutate() override { throw ActionDenied(4); }
	void rezervaCarte(std::string carte) override { throw ActionDenied(11); }
	void returneazaCarte(std::string Carte) override { throw ActionDenied(12); }
	void prelungireTermen(std::string numeCarte) override { throw ActionDenied(5); }
};

