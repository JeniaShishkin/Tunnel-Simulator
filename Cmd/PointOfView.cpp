#include "PointOfView.h"

namespace jb
{
std::string CmdPointOfView::execute() const
{
    std::stringstream out;
    if (!m_ctx.activeSensor)
    {
        out << "No sensor selected\n";
        return out.str();
    }
    out = m_ctx.activeSensor->scan(m_ctx.m_grid, m_ctx.m_position, m_ctx.m_compass);
    
    return out.str();
}
}
