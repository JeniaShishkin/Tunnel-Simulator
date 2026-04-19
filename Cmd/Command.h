#ifndef __Command_h__
#define __Command_h__

#include "../BaseEssentials.h"
#include <sstream>

namespace jb
{

struct Command : private BaseEssentials
{
	Command() = default;
	virtual std::string execute() const = 0;
	virtual ~Command() = default;


};

} // jb

#endif
