#pragma once
#include <string>

class IArticol;
enum class TipArticol;
class FactoryArticol
{
public:
	static IArticol* getArticol(std::string numeCarte);
	static IArticol* createArticol(std::string nume, TipArticol type);
};

