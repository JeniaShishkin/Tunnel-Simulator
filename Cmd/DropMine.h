#ifndef __DROPMINE_H__
#define __DROPMINE_H__

#include <iostream>

#include "Command.h"
#include "../Navigation/WorldGrid.h"
#include "../Navigation/Position.h"
#include "../Navigation/Compass.h"

namespace jb
{

class CmdPlantMine : public Command
{
public:
	explicit CmdPlantMine(WorldGrid *grid, Position *position, const Compass *compass) : m_grid(*grid), m_position(*position), m_compass(*compass) { }
	virtual std::string execute() const override;
    ~CmdPlantMine() = default;

private:
	WorldGrid &m_grid;
	Position &m_position;
	const Compass &m_compass;
};

} // jb

#endif
