#include "TurnRight.h"
#include "../Navigation/Compass.h"
#include <iostream>

namespace jb
{

std::string CmdTurnRight::execute() const
{
	std::stringstream out;
	turnRight(&m_compass);
	out << "turned right. now facing " << m_compass.getHeading() << std::endl;
	return out.str();
}


} // jb
