#ifndef __MAP_H__
#define __MAP_H__

#include "Command.h"
#include "../Navigation/WorldGrid.h"

namespace jb
{


class CmdMap : public Command
{
public:
    explicit CmdMap(const WorldGrid& grid) : m_grid(grid) { } 
    virtual std::string execute() const override;
    ~CmdMap() = default;

private:
    const WorldGrid& m_grid;

};

}

#endif