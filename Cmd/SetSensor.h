#ifndef __SETSENSOR_H__
#define __SETSENSOR_H__

#include "Command.h"
#include "Context.h"
#include "../Sensors/Sensor.h"

namespace jb
{
class SetSensor: public Command
{
public:
    SetSensor(Context& c, const Sensor& s) : m_ctx(c), m_sensor(s) { }

    std::string execute() const override { m_ctx.activeSensor = &m_sensor; }

    ~SetSensor() = default;
private:
    Context& m_ctx;
    const Sensor& m_sensor;

};
}


#endif