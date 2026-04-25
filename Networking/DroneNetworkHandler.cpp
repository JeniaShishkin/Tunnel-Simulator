#include <iostream>
#include <cassert>
#include "DroneNetworkHandler.h"
#include "../Session.h"

namespace jb
{

void DroneNetworkHandler::onNewConnection(size_t socketId)
{
    PutOutput(socketId,"> Please choose a drone: A, B, or C: ");
    m_openSessions.emplace(socketId, nullptr);
    // m_openSessions.emplace(socketId, std::make_unique<Session>());
}

void DroneNetworkHandler::onConnectionClosed(size_t socketId)
{
    PutOutput(socketId, "Connection terminated by " + socketId);
    auto existing = m_openSessions.find(socketId);
    assert(existing != m_openSessions.end());
//    m_sessionCleaner(existing->second.get()); 
    m_openSessions.erase(existing);
    if (m_openSessions.empty()) { m_run = false; }
}


void DroneNetworkHandler::process(size_t socketId, std::string& input)
{
    auto& session = m_openSessions[socketId];
    
    if (!session) { session = std::make_unique<Session>(input); } 
    
    PutOutput(socketId, session->handle(input));
}

}