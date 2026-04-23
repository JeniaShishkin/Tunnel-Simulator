#ifndef __DRONETILE_H__
#define __DRONETILE_H__


#include "Tile.h"

namespace jb
{
class DroneTile : public Tile
{
public:
    explicit DroneTile() = default;
	virtual bool canOccupy() const override { return true; }
	virtual char symbol() const override { return 'D'; } 
    ~DroneTile() = default;

private:

};
}


#endif