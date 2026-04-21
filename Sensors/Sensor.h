#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <sstream>
#include <map>

#include "../Navigation/WorldGrid.h"
#include "../Navigation/Position.h"
#include "../Navigation/Compass.h"
namespace jb
{

/* ------ HEADING-BASED SENSOR INVORMATION ------ */
struct BoundsOffset {
    Position start;
    Position end;
};

using BoundsMap = std::map<int, BoundsOffset>;



class Sensor
{
public:
    Sensor() = default;
    virtual std::stringstream scan(const WorldGrid& grid, const Position& pos, const Compass& compass) const = 0;
    virtual std::pair<Position, Position> getIterationBoundaries(const Position& pos, const Compass& compass) const = 0;
    ~Sensor() = default;

};

}

#endif