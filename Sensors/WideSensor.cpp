#include "WideSensor.h"
#include "../Navigation/WorldGrid.h"
#include "../Navigation/Position.h"
#include "../Tiles/Tile.h"

namespace jb
{
std::stringstream WideSensor::scan(const WorldGrid& grid, const Position& pos, const Compass& compass) const 
{ 
    std::stringstream out;
    out << "Wide Sensor invoked." << std::endl;
    Position start{pos.getX() - 1,pos.getY() - 2};
    
    Position end{pos.getX() - 1,pos.getY() + 2};
    int prevX = start.getX();
    for (auto it = grid.begin(start, end); it != grid.end(start, end); ++it)
    {
        if (it.getCurrentX() != prevX)
        {
            out << '\n';
            prevX = it.getCurrentX();
        }
        out << "I enter here" << std::endl;
        out << (*it)->symbol(); 
    }
    out << std::endl;
    
    return out;
}
}