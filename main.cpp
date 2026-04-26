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
#include "Session.h"
#include "Networking/DroneNetworkHandler.h"

using namespace jb;

static DroneNetworkHandler nh{9000};


int main()
{
	size_t socketId;
	std::string input;
	while(nh.isRunning())
	{
		nh.GetInput(&socketId, &input);
		if(!input.empty()) 
		{ 
			nh.process(socketId, input); 
		}
	}
	return 0;
}

