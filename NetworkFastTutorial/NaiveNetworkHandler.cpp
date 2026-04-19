#include <iostream>
#include "NaiveNetworkHandler.h"

void NaiveNetworkHandler::onNewConnection(size_t socketId) const
{
    std::cout << "This is a new connection" << std::endl;
}

void NaiveNetworkHandler::onConnectionClosed(size_t socketId) const 
{
    std::cout << "Connection closed." << std::endl;
}