#ifndef __CmdBackward_h__
#define __CmdBackward_h__

#include <iostream>

#include "Command.h"
#include "../Navigation/WorldGrid.h"
#include "../Navigation/Position.h"
#include "../Navigation/Compass.h"

namespace jb
{

class CmdBackward : public Command
{
public:
	CmdBackward(WorldGrid *grid, Position *position, const Compass *compass) : m_grid(*grid), m_position(*position), m_compass(*compass) { }

	virtual std::string execute() const override;

private:
	WorldGrid &m_grid;
	Position &m_position;
	const Compass &m_compass;
};

} // jb

#endif
