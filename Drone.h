#ifndef __Drone_h__
#define __Drone_h__

#include <iostream>
#include <string>
#include <string_view>
#include <map>
#include <cassert>
#include <sstream>

#include "Navigation/WorldGrid.h"
#include "Tiles/Tile.h"

/* COMMAND INCLUDES */
#include "Cmd/Command.h"
#include "Cmd/Forward.h"
#include "Cmd/TurnLeft.h"
#include "Cmd/TurnRight.h"
#include "Cmd/Execute.h"
#include "Cmd/PointOfView.h"
#include "Cmd/Map.h"
#include "Cmd/SetSensor.h"

/* SENSOR INCLUDES */
#include "Cmd/Context.h"
#include "Sensors/Sensor.h"
#include "Sensors/WideSensor.h"
#include "Sensors/CircularSensor.h"
#include "Sensors/DistanceSensor.h"

namespace jb
{

using TypeId = std::string;
class Drone 
{
public:
// Command controlling variable.
	using CommandsMap = std::map<std::string, std::unique_ptr<Command>>;
	const WorldGrid m_grid;
	bool doLoop = true;

	using Sensors = std::vector<std::shared_ptr<Sensor>>;
	Drone(WorldGrid grid, Compass compass, Position position, unsigned int energy, Sensors sensors);
	bool reachedExit();
	const CommandsMap& getCommand() const { return m_commands; }
	~Drone() = default;
private:
	Compass m_compass;
	Position m_position;
	Context m_ctx;
	unsigned int m_energy;
	std::vector<std::shared_ptr<Sensor>> m_sensors;

	// Drone commands map.
	CommandsMap m_commands;


};

using DroneFactory = std::function<Drone()>;
using DroneConfigByType = std::unordered_map<TypeId, DroneFactory>;

static const DroneConfigByType DRONE_CONFIGS = {
	{"A", [] { 
		return Drone{WorldGrid{}, Compass{NORTH}, Position{0,1}, 300, {std::make_shared<WideSensor>()}};
	}},
	{"B", [] {
		return Drone{WorldGrid{}, Compass{NORTH}, Position{0,1}, 500, {std::make_shared<WideSensor>(), std::make_shared<CircularSensor>()}};
	}},
	{"C", [] {
		return Drone{WorldGrid{}, Compass{NORTH}, Position{0,1}, 400, {std::make_shared<WideSensor>()}};
	}},
}; 


} // jb


#endif
