#pragma once
#include <string>

class Imprumut
{
private:
	std::string username;

public:
	Imprumut(std::string username);

	void afisareCartiImprumutate(int command);
	void prelungireTermen(std::string numeCarte);
	
	void afiseazaImprumuturiExp_B();
};

