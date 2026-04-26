#include "DropMine.h"

namespace jb
{
std::string CmdPlantMine::execute() const 
{
	std::stringstream out;
    Compass opposite = m_compass;
    turnLeft(&opposite);
    turnLeft(&opposite);
	Position newPosition = advance(m_position, opposite);
	if (m_grid.getTile(newPosition.getX(), newPosition.getY()).canOccupy())
	{
		out << "Placed mine." << std::endl; 
		m_grid.placeMine(newPosition);
	}
	else
	{
		out << "unable to place mine - wall behind you." << std::endl; 
	}
	return out.str();
}


}