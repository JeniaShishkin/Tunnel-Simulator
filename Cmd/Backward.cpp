#include "Backward.h"

namespace jb
{


std::string CmdBackward::execute() const 
{
	std::stringstream out;
    Compass opposite = m_compass;
    turnLeft(&opposite);
    turnLeft(&opposite);
	Position newPosition = advance(m_position, opposite);
	if (m_grid.getTile(newPosition.getX(), newPosition.getY()).canOccupy())
	{
		out << "backward" << std::endl; 
		m_grid.updatePosition(m_position, newPosition);
		m_position = newPosition;
	}
	else
	{
		out << "blocked" << std::endl; 
	}
	return out.str();
}


}