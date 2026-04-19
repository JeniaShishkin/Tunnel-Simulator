#ifndef __TurnRight_h__
#define __TurnRight_h__

#include "Command.h"

namespace jb
{

class Compass;

class CmdTurnRight : public Command 
{
public:
	CmdTurnRight(Compass *compass) : m_compass(*compass) { }

	virtual std::string execute() const override;

private:
	Compass &m_compass;
};

} // jb

#endif
