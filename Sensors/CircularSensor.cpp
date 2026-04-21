#include "CircularSensor.h"
#include "../Navigation/WorldGrid.h"
#include "../Navigation/Position.h"
#include "../Tiles/Tile.h"
#include <map>

namespace jb
{


std::stringstream CircularSensor::scan(const WorldGrid& grid, const Position& pos, const Compass& compass) const 
{ 
    std::stringstream out;
    out << "Circular sensor invoked" << std::endl;
    const auto [start, end] = getIterationBoundaries(pos, compass);
    int prevX = start.getX();
    for (auto it = grid.begin(start, end); it != grid.end(start, end); ++it)
    {
        if (it.getCurrentX() != prevX)
        {
            out << '\n';
            prevX = it.getCurrentX();
        }
        out << (*it)->symbol();
    }
    out << std::endl;
    return out;
}


std::pair<Position, Position> CircularSensor::getIterationBoundaries(const Position& pos, const Compass& compass) const
{
    auto it = CIRCULAR_BOUNDS.find(compass.getHeading());
    if (it == CIRCULAR_BOUNDS.end())
    {
        throw std::runtime_error("Invalid Heading");
    }
    const auto& offset = it->second;
    Position start{pos.getX() + offset.start.getX(), pos.getY() + offset.start.getY()};
    Position end{pos.getX() + offset.end.getX() ,pos.getY() + offset.end.getY()};
    return {start,end};
}
}