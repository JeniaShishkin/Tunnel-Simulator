#ifndef __MINETILE_H__
#define __MINETILE_H__

#include "Tile.h"

namespace jb
{

class MineTile : public Tile 
{
public:
    explicit MineTile() = default;
	virtual bool canOccupy() const override { return true; }
	virtual char symbol() const override { return '@'; } 
    ~MineTile() = default;
};

} // jb


#endif