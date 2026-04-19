#ifndef __CmdForward_h__
#define __CmdForward_h__

#include <iostream>
#include "Command.h"

// TODO: Demonstrate how to get rid of these includes !!!!!!!!!!!!!!!!!!
#include "../Navigation/WorldGrid.h"
#include "../Navigation/Position.h"
#include "../Navigation/Compass.h"

namespace jb
{

class CmdForward : public Command
{
public:
	CmdForward(const WorldGrid *grid, Position *position, const Compass *compass) : m_grid(*grid), m_position(*position), m_compass(*compass) { }

	virtual std::string execute() const override;

private:
	const WorldGrid &m_grid;
	Position &m_position;
	const Compass &m_compass;
};

} // jb

#endif
