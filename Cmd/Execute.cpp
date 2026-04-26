#include "Execute.h"
#include "../Navigation/Compass.h"
#include <iostream>

namespace jb
{

std::string CmdExecute::execute() const
{
	m_toExecute();
    return "";
}


} // jb
