#include "AbsArticol.h"
#include "IQuery.h"
#include "FactoryQuery.h"
#include "RetainSelect.h"

AbsArticol::AbsArticol(std::string name, TipArticol art): name(name), art(art)
{
}
