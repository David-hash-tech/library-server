#pragma once
#include <string>
#include <vector>

class IUser
{
public:
	virtual const int& getSocketID() = 0;
	virtual void setSocketID(int Socket) = 0;


	virtual void afisareProfil() = 0;
	virtual void afisareProgram() = 0;
	virtual void afisareContact() = 0;
	virtual void cauta(std::string articol) = 0;
	virtual void descarcaArticol(std::string articol) = 0;
	virtual void afiseazaDetaliiArticol(std::string articol) = 0;
	virtual void deconectare() = 0;

	virtual void schimbaEmail(std::string newEmail) = 0;
	virtual void schimbaTelefon(std::string newTelefon) = 0;
	virtual void schimbaParola(std::string newPassword) = 0;

	virtual void rezervaCarte(std::string carte) = 0;
	virtual void afisareCartiImprumutate() = 0;
	virtual void returneazaCarte(std::string Carte) = 0;
	virtual void prelungireTermen(std::string numeCarte) = 0;


	virtual void adaugaArticol_B(std::vector<std::string> parameters) = 0;
	virtual void eliminaArticol_B(std::string articol) = 0;
	virtual void modificaArticol_B(std::vector<std::string> parameters) = 0;
	virtual void afiseazaImprumuturiExp_B() = 0;
};