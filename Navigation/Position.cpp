#include "Position.h"
#include <map>
#include <stdexcept>
#include <iostream>

namespace jb
{
struct PositionDelta
{
	int deltaX;
	int deltaY;
};

using DeltasMap = std::map<const int, const PositionDelta>;
static const DeltasMap DELTAS { 
	{ 0, { -1, 0 } }, 
	{ 90, { 0 , 1 } }, 
	{ 180, { 1 , 0 } }, 
	{ 270, { 0 , -1 } }
};


Position advance(const Position &cur, const Compass &heading)
{
	DeltasMap::const_iterator deltaItr = DELTAS.find(heading.getHeading());
	if (deltaItr == DELTAS.end())
	{
		throw std::runtime_error{"Unprocessable compass heading"};
	}
	return Position{cur.getX() + deltaItr->second.deltaX, cur.getY() + deltaItr->second.deltaY};
}


} // jb
