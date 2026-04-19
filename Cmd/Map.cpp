#include "Map.h"
#include "../Navigation/Position.h"
#include "../Tiles/Tile.h"

namespace jb
{

std::string CmdMap::execute() const
{
    std::stringstream out;
    Position start{0,0};
    
    Position end{m_grid.getRowSize(),m_grid.getColSize()};
    int prevX = start.getX();
    for (auto it = m_grid.begin(start, end); it != m_grid.end(start, end); ++it)
    {
        if (it.getCurrentX() != prevX)
        {
            out << '\n';
            prevX = it.getCurrentX();
        }
        out << (*it)->symbol(); // or however you print
    }
    out << std::endl;

    return out.str();
}

}