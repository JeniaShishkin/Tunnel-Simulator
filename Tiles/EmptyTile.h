#ifndef __EmptyTile_h__
#define __EmptyTile_h__

#include "Tile.h"

namespace jb
{

class EmptyTile : public Tile 
{
public:
	explicit EmptyTile() = default;
	virtual bool canOccupy() const { return true; }
	virtual char symbol() const override { return '.'; } 
	~EmptyTile() = default;
};

} // jb

#endif
