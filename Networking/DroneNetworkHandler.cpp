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
}

void DroneNetworkHandler::onConnectionClosed(size_t socketId)
{
    PutOutput(socketId, "Connection terminated by " + socketId);
    auto existing = m_openSessions.find(socketId);
    if(existing != m_openSessions.end()) { m_openSessions.erase(existing); }
    if (m_openSessions.empty()) { m_run = false; }
}


void DroneNetworkHandler::process(size_t socketId, std::string& input)
{
    auto& session = m_openSessions[socketId];
    
    if (!session)
    { 
        try { PutOutput(socketId, "> "); session = std::make_unique<Session>(input); } 
        catch (std::out_of_range& e) { PutOutput(socketId, "Invalid drone, please try again.\n> Please choose a drone: A, B, or C: ");  return; }
        
    } 
    
    if (session->isInitialized())
    {
        std::string stringResult = session->handle(input);
        if (stringResult == "EXIT")
        {
            /* TO ADD EXIT LOGIC */
            return;
        }
        PutOutput(socketId, stringResult + "\n> "); 
    }
    
    else { session->markInitialized(); }
}

}