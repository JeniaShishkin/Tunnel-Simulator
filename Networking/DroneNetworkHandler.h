#ifndef __DroneNetworkHandler_H__
#define __DroneNetworkHandler_H__

#include "NetworkHandler.h"
#include <unordered_map>
#include <memory>


namespace jb
{
class Session;
class DroneNetworkHandler : public whytsoft::NetworkHandler
{
public:
    explicit DroneNetworkHandler(short unsigned int socketId) : NetworkHandler{socketId}, m_run(true) { }
    virtual void onNewConnection(long long unsigned int socketId) override;
	virtual void onConnectionClosed(long long unsigned int socketId) override;
    void process(size_t socketId, std::string& input);
    bool isRunning() { return m_run; }
    ~DroneNetworkHandler() = default;
    
private:
    bool m_run;
    std::unordered_map<size_t, std::unique_ptr<Session>> m_openSessions;
};

}

#endif