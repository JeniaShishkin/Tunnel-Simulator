#ifndef __Command_h__
#define __Command_h__

#include <functional>
#include <sstream>
#include <memory>
#include <iostream>
#include <string>
#include <string_view>
#include <map>
#include <cassert>

#include "../Navigation/WorldGrid.h"
#include "../Navigation/Compass.h"
#include "../Navigation/Position.h"
#include "../Tiles/Tile.h"


/* SENSOR INCLUDES */
#include "Context.h"
#include "../Sensors/Sensor.h"
#include "../Sensors/WideSensor.h"
#include "../Sensors/CircularSensor.h"
#include "../Sensors/DistanceSensor.h"
#include "../BaseEssentials.h"

namespace jb
{

/* Added functionality via compile-time decorator */	
class Command;

using CommandsMap = std::map<std::string, std::unique_ptr<Command>>;

template<class CmdT, unsigned int CONSUMPTION>
struct FixedConsumption : public CmdT
{
    FixedConsumption(WorldGrid *grid, Position *position, const Compass *compass) : CmdT(grid, position, compass) { }
    FixedConsumption(Compass *compass) : CmdT(compass) { }
    FixedConsumption(const WorldGrid& grid) : CmdT(grid) { }
    FixedConsumption(const Context &ctx) : CmdT(ctx) { }
    FixedConsumption(Context &ctx, const std::shared_ptr<Sensor> s) : CmdT(ctx, s) { }
    FixedConsumption(std::function<void()> func) : CmdT(func) { }
   
    virtual unsigned int getEnergyConsumption() const override { return CONSUMPTION; } 
};


struct Command : private BaseEssentials
{
	Command() = default;
	virtual std::string execute() const = 0;
	virtual unsigned int getEnergyConsumption() const { return 0; }

	virtual ~Command() = default;

	


};

} // jb

#endif
