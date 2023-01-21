#include "AbsException.h"

AbsException::AbsException(int command, std::string msg): command(command)
{
	this->msg = std::to_string(command) + "/" + msg;
}