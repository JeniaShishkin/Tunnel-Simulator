#ifndef __TurnLeft_h__
#define __TurnLeft_h__

#include "Command.h"

namespace jb
{

class Compass;

class CmdTurnLeft : public Command 
{
public:
	CmdTurnLeft(Compass *compass) : m_compass(*compass) { }

	virtual std::string execute() const override;

private:
	Compass &m_compass;
};

} // jb

#endif
