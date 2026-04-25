#ifndef __SESSION_H__
#define __SESSION_H__

#include <optional>
#include <string>
#include <memory>
#include <functional>

#include "Cmd/Command.h"
#include "Networking/DroneNetworkHandler.h"
#include "Navigation/WorldGrid.h"
#include "Navigation/Compass.h"
#include "Navigation/Position.h"
#include "Drone.h"

namespace jb
{
class Session
{
public:
    using CommandsMap = std::map<std::string, std::unique_ptr<Command>>;

    Session(const std::string& input) : m_drone(DRONE_CONFIGS.at(input)()) { }
    const Position& getPosition() const { return m_drone.getPosition(); }
    std::optional<std::reference_wrapper<Command>> getCommand(const std::string& s) const { return *m_drone.getCommand().at(s); }
    const Drone& getCurrentDrone() { return m_drone; }
    bool canExecute(const Command& cmd) const;
    std::string handle(std::string& input);

    ~Session() = default;
    // void consume(const Command& cmd, const OutputContext& output);

    
private:
    const Drone m_drone;
};

}

#endif