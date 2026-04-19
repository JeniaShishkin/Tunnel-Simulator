#ifndef __CmdExecute_h__
#define __CmdExecute_h__

#include <functional>
#include "Command.h"

namespace jb
{

class CmdExecute : public Command 
{
public:
	CmdExecute(const std::function<void()> &toExecute) : m_toExecute(toExecute) { }
	CmdExecute(const std::function<void()> &&toExecute) : m_toExecute(std::move(toExecute)) { }

	virtual std::string execute() const override;

private:
	std::function<void()> m_toExecute;
};

} // jb

#endif
