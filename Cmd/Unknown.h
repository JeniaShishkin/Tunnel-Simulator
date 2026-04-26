#ifndef __UNKNOWN_H__
#define __UNKNOWN_H__

#include "Command.h"
namespace jb
{


struct CmdUnknown : public Command
{
	virtual std::string execute() const override { std::stringstream buffer; buffer << "ERROR: Unknown command\n"; return buffer.str(); }
    virtual unsigned int getEnergyConsumption() const override { return 0; }
} CMD_UNKNOWN;

}

#endif