#ifndef __DISTANCESENSOR_H__
#define __DISTANCESENSOR_H__

#include <iostream>
#include "Sensor.h"
#include "../Navigation/Compass.h"

namespace jb
{
    inline const BoundsMap DISTANCE_BOUNDS {
    { 0,   {{ -3 , -2 }, { -1,  2}}},    // NORTH
    { 90,  {{ -2 , 1 },  { 2 , 3 }}},    // EAST
    { 180, {{ 1 , -2 },  { 3 ,  2 }}},   // SOUTH
    { 270, {{ -2 , -3 },  { -2 ,  -1 }}} // WEST
};

class DistanceSensor : public Sensor
{
public:
    DistanceSensor() = default;
    virtual std::stringstream scan(const WorldGrid& grid, const Position& pos, const Compass& compass) const override;
    virtual std::pair<Position, Position> getIterationBoundaries(const Position& pos, const Compass& compass) const override;

    ~DistanceSensor() = default;

private:

};
}

#endif