#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <sstream>
#include "../Navigation/WorldGrid.h"
#include "../Navigation/Position.h"
#include "../Navigation/Compass.h"
namespace jb
{

class Sensor
{
public:
    Sensor() = default;
    virtual std::stringstream scan(const WorldGrid& grid, const Position& pos, const Compass& compass) const = 0;
    ~Sensor() = default;

};

}

#endif