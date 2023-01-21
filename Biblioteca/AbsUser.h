#pragma once
#include "IUser.h"
#include <iostream>
#include "TipAbonament.h"

class AbsUser :
    public IUser
{
protected:
    int Socket;
    std::string username;
    TipAbonament Ab;

public:
    AbsUser();
    AbsUser(int Socket, std::string username, TipAbonament Ab);


    void afisareProfil() override;
    void afisareProgram() override;
    void afisareContact() override;
    void cauta(std::string articol)override;
    void descarcaArticol(std::string articol)override;
    void afiseazaDetaliiArticol(std::string articol) override;
    void deconectare() override;


    void schimbaEmail(std::string newEmail) override;
    void schimbaTelefon(std::string newTelefon) override;
    void schimbaParola(std::string newPassword) override;


    const int& getSocketID() { return this->Socket; }
    const TipAbonament& getTipAbonament() { return this->Ab; }
    const std::string& getUsername() { return this->username; }


    void setSocketID(int Socket) { this->Socket = Socket; }
    const TipAbonament& getTipAbonament(TipAbonament Ab) { this->Ab = Ab; }
    void setUsername(std::string newUsername) { this->username = newUsername; }
};
