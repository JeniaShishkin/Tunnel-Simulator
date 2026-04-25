#include "Session.h"
#include "Cmd/Command.h"

namespace jb
{

Command &parseCommand(const CommandsMap &commands, const std::string &s);

struct CmdUnknown : public Command
{
	virtual std::string execute() const override { std::stringstream buffer; buffer << "ERROR: Unknown command\n"; return buffer.str(); }
    virtual unsigned int getEnergyConsumption() const override { return 0; }
} CMD_UNKNOWN;


std::string Session::handle(std::string& input)
{  	
    if (!m_drone.doLoop || m_drone.reachedExit())
        return "EXIT";

    const Command& cmd = parseCommand(m_drone.getCommand(), input);
    return cmd.execute();

/* 	while (m_drone.doLoop && !m_drone.reachedExit())
	{
		nh.GetInput(&socketId, &input);        
		const Command &cmd = parseCommand(m_drone.getCommand(), input);
		std::string buffer;
		try
		{
			buffer = cmd.execute();
			nh.PutOutput(socketId, buffer);
			nh.PutOutput(socketId,"> ");
		}
		catch(std::exception& e)
		{
			nh.PutOutput(socketId, e.what());
			break;
		}
	} */
}



/*     const Command &cmd = parseCommand(m_drone.getCommand(), input);
    std::string output = cmd.execute();
    if (m_drone.reachedExit())
    {
        output += "\nEXIT REACHED";
        m_drone.doLoop = false;
    }

    return output; */


Command &parseCommand(const CommandsMap &commands, const std::string &s)
{
	CommandsMap::const_iterator cmdItr = commands.find(s);
	if (cmdItr == commands.end())
	{
		return CMD_UNKNOWN;
	}
	return *(cmdItr->second);
}




}