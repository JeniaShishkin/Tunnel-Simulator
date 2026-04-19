#include "DistanceSensor.h"
#include "../Navigation/WorldGrid.h"
#include "../Navigation/Position.h"
#include "../Tiles/TIle.h"

namespace jb
{
std::stringstream DistanceSensor::scan(const WorldGrid& grid, const Position& pos, const Compass& compass) const 
{ 
    std::stringstream out;
    out << "Distance Sensor invoked." << std::endl;
    int x = pos.getX();
    int y = pos.getY();

    Position start{x - 3, y - 2};
    Position end  {x - 1, y + 2}; 

    int baseX = start.getX();
    int centerY = y;

    for (auto it = grid.begin(start, end); it != grid.end(start, end); ++it)
    {
        int curX = it.getCurrentX();
        int curY = it.getCurrentY();

        int dx = (start.getX() + 2) - curX; 
        int allowedWidth = dx * 2 + 1; 

        int leftBound = centerY - dx;
        int rightBound = centerY + dx;

        if (curY < leftBound || curY > rightBound) { continue; }

        if (curY == leftBound) { out << '\n'; }

        out << (*it)->symbol();
    }

    out << '\n';

    return out;
}
}