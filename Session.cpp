#include "Session.h"
#include "Cmd/Unknown.h"

namespace jb
{

Command &parseCommand(const CommandsMap &commands, const std::string &s)
{
	CommandsMap::const_iterator cmdItr = commands.find(s);
	if (cmdItr == commands.end())
	{
		return CMD_UNKNOWN;
	}
	return *(cmdItr->second);
}	

std::string Session::handle(std::string& input)
{  	
    const Command& cmd = parseCommand(m_drone.getCommand(), input);

	std::string executionResult = cmd.execute();

	if (!m_drone.doLoop || m_drone.reachedExit()) { return "EXIT"; }
	
	else { return executionResult; }
}

}