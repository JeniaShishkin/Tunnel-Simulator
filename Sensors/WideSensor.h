#ifndef __WIDESENSOR_H__
#define __WIDESENSOR_H__

#include "Sensor.h"
#include "../Navigation/Compass.h"
namespace jb
{

inline const BoundsMap WIDE_BOUNDS {
    { 0,   {{ -1 , -2 }, { -1,  2}}},    // NORTH
    { 90,  {{ -2 , 1 },  { 2 , 1 }}},    // EAST
    { 180, {{ 1 , -2 },  { 1 ,  2 }}},   // SOUTH
    { 270, {{ -2 , -1 },  { 2 ,  -1 }}}  // WEST
};

class WideSensor : public Sensor
{
public:
    WideSensor() = default;
    virtual std::stringstream scan(const WorldGrid& grid, const Position& pos, const Compass& compass) const override;
    virtual std::pair<Position, Position> getIterationBoundaries(const Position& pos, const Compass& compass) const override;
    ~WideSensor() = default;
};
}


#endif