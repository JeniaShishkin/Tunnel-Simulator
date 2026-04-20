#include <iostream>
#include <string>
#include <string_view>
#include <map>
#include <cassert>
#include <sstream>

#include "Drone.h"
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

/* NETWORKING */
#include "Networking/NaiveNetworkHandler.h"

using namespace jb;

Command &parseCommand(const CommandsMap &commands, const std::string &s);


struct CmdUnknown : public Command
{
	virtual std::string execute() const override { std::stringstream buffer; buffer << "ERROR: Unknown command\n"; return buffer.str(); }
    virtual unsigned int getEnergyConsumption() const override { return 0; }
} CMD_UNKNOWN;


static NaiveNetworkHandler nh{9000};
static size_t socketId;


int main()
{
    static std::string input;
    nh.GetInput(&socketId, &input);
    nh.PutOutput(socketId,"> Please enter desired drone: A, B, or C: ");
    nh.GetInput(&socketId, &input);
    nh.PutOutput(socketId,"> ");

    Drone currentDrone = DRONE_CONFIGS.at(input)();
 
    std::cout << !currentDrone.doLoop << " " << !currentDrone.reachedExit() << std::endl;
	while (currentDrone.doLoop && !currentDrone.reachedExit())
	{
        nh.GetInput(&socketId, &input);
		if (input.empty())
		{
            nh.PutOutput(socketId,"> ");
            continue;
		}

		Command &cmd = parseCommand(currentDrone.getCommand(), input);
		std::string buffer = cmd.execute();
        nh.PutOutput(socketId, buffer);
        nh.PutOutput(socketId,"> ");
	}
}

Command &parseCommand(const CommandsMap &commands, const std::string &s)
{
	CommandsMap::const_iterator cmdItr = commands.find(s);
	if (cmdItr == commands.end())
	{
		return CMD_UNKNOWN;
	}
	return *(cmdItr->second);
}

