#include "Forward.h"
#include "../Tiles/Tile.h"
#include <sstream>
namespace jb
{

std::string CmdForward::execute() const 
{ 
	std::stringstream out;
	Position newPosition = advance(m_position, m_compass);
	if (m_grid.getTile(newPosition.getX(), newPosition.getY()).canOccupy())
	{
		out << "forward" << std::endl; 
		m_position = newPosition;
	}
	else
	{
		out << "blocked" << std::endl; 
	}
	return out.str();
}

} // jb
