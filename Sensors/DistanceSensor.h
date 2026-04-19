#ifndef __DISTANCESENSOR_H__
#define __DISTANCESENSOR_H__

#include <iostream>
#include "Sensor.h"
#include "../Navigation/Compass.h"

namespace jb
{

class DistanceSensor : public Sensor
{
public:
    DistanceSensor() = default;
    virtual std::stringstream scan(const WorldGrid& grid, const Position& pos, const Compass& compass) const override;
    ~DistanceSensor() = default;

private:

};
}

#endif