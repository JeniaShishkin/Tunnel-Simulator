#ifndef __CIRCULARSENSOR_H__
#define __CIRCULARSENSOR_H__

#include <map>

#include "Sensor.h"
#include "../Navigation/Compass.h"
namespace jb
{


inline const BoundsMap CIRCULAR_BOUNDS {
    { 0,   { {-2, -2}, { 1,  1} } }, // NORTH
    { 90,  { {-1, -1},  {1,  2 }} }, // EAST
    { 180, { {-1, -1},  {2,  1 }} }, // SOUTH
    { 270, { {-1, -2},  {1,  1 }} }  // WEST
};

class CircularSensor : public Sensor
{
public:
    CircularSensor() = default;
    virtual std::stringstream scan(const WorldGrid& grid, const Position& pos, const Compass& compass) const override;
    std::pair<Position, Position> getIterationBoundaries(const Position& pos, const Compass& compass) const override;
    ~CircularSensor() = default;
};
}

#endif
