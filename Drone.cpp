#include "Drone.h"


namespace jb
{
Drone::Drone(WorldGrid grid, Compass compass, Position position, unsigned int energy, Sensors sensors) : 
		m_grid(grid), m_compass(compass), m_position(position), m_sensors(sensors), m_ctx{grid, position, compass}
{
	std::shared_ptr<Sensor> circular, wide, distance;

	for (auto& s : sensors) {
	    if (dynamic_cast<CircularSensor*>(s.get())) { circular = s; }
	    if (dynamic_cast<WideSensor*>(s.get())) { wide = s; }
	    if (dynamic_cast<DistanceSensor*>(s.get())) { distance = s; }
	}
	 m_commands.emplace("fwd", std::make_unique<FixedConsumption<CmdForward, 10>>(&grid, &position, &compass));
	 m_commands.emplace("+90", std::make_unique<FixedConsumption<CmdTurnLeft, 10>>(&compass));
	 m_commands.emplace("-90", std::make_unique<FixedConsumption<CmdTurnRight, 10>>(&compass));
	 m_commands.emplace("exit", std::make_unique<CmdExecute>([this]() { doLoop=false;}));
	 m_commands.emplace("pov" , std::make_unique<FixedConsumption<CmdPointOfView, 10>>(m_ctx));
	 m_commands.emplace("map", std::make_unique<FixedConsumption<CmdMap, 10>>(grid));
	 m_commands.emplace("s_a", std::make_unique<FixedConsumption<SetSensor, 10>>(m_ctx, circular));
	 m_commands.emplace("s_b", std::make_unique<FixedConsumption<SetSensor, 10>>(m_ctx, wide));
	 m_commands.emplace("s_c", std::make_unique<FixedConsumption<SetSensor, 10>>(m_ctx, distance));
}

bool Drone::reachedExit()
{
	return m_grid.getTile(m_position.getX(), m_position.getY()).shouldExit();
}

}