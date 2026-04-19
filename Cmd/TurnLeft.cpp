#include "TurnLeft.h"
#include "../Navigation/Compass.h"
#include <iostream>

namespace jb
{

std::string CmdTurnLeft::execute() const
{
	std::stringstream out;
	turnLeft(&m_compass);
	out << "turned left. now facing " << m_compass.getHeading() << std::endl;
	return out.str();
}


} // jb
