#pragma once
#include "AbsUser.h"
#include "ActionDenied.h"

class Client :
    public AbsUser
{
private:
    std::string CNP;
    std::string Email;
    std::string Telefon;

public:
    Client();
    Client(int Socket, std::string username, TipAbonament Ab);


    void afisareCartiImprumutate() override;
    void rezervaCarte(std::string carte) override;
    void returneazaCarte(std::string Carte) override;
    void prelungireTermen(std::string numeCarte) override;


    std::string getCNP() { return this->CNP; }
    std::string getEmail() { return this->Email; }
    std::string getTelefon() { return this->Telefon; }


    void setCNP(std::string newCNP) { this->CNP = newCNP; }
    void setEmail(std::string newEmail) { this->Email = newEmail; }
    void setTelefon(std::string newTelefon) { this->Telefon = newTelefon; }


    void afiseazaImprumuturiExp_B()override { throw ActionDenied(15); }
    void eliminaArticol_B(std::string articol)override { throw ActionDenied(17); }
    void adaugaArticol_B(std::vector<std::string> parameters)override { throw ActionDenied(14); }
    void modificaArticol_B(std::vector<std::string> parameters)override { throw ActionDenied(16); }
};
