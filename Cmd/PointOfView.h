#ifndef _POINTOFVIEW_H__
#define _POINTOFVIEW_H__

#include <iostream>
#include <map>
#include "Command.h"
#include "../Navigation/Position.h"
#include "../Navigation/Compass.h"
#include "../Navigation/WorldGrid.h"
#include "../Tiles/Tile.h"
#include "Context.h"

namespace jb
{

struct PositionDelta
{
	int deltaX;
	int deltaY;
};

using DeltasMap = std::map<Compass, const PositionDelta>;

static const DeltasMap DELTAS { 
	{ NORTH, { -1, 0 } }, 
	{ EAST, { 1, 0 } }, 
	{ SOUTH, { 0, -1 } }, 
	{ WEST, { -1, 0 } }
};


class CmdPointOfView : public Command
{
public:
    explicit CmdPointOfView(const Context& ctx) : m_ctx(ctx) { }
    virtual std::string execute() const override;
    ~CmdPointOfView() = default;

private:
    const Context& m_ctx;
};

}

#endif
