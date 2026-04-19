#ifndef __WIDESENSOR_H__
#define __WIDESENSOR_H__

#include "Sensor.h"
#include "../Navigation/Compass.h"
namespace jb
{

class WideSensor : public Sensor
{
public:
    WideSensor() = default;
    virtual std::stringstream scan(const WorldGrid& grid, const Position& pos, const Compass& compass) const override;
};
}


#endif