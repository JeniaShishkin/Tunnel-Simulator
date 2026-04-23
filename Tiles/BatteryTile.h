#ifndef __BATTERYTILE_H__
#define __BATTERYTILE_H__


#include "Tile.h"

namespace jb
{
class BatteryTile : public Tile
{
public:
    explicit BatteryTile() = default;
	virtual bool canOccupy() const override { return true; }
	virtual char symbol() const override { return '%'; } 
    ~BatteryTile() = default;

private:

};
}


#endif