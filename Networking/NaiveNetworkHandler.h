#ifndef __NAIVENETWORKHANDLER_H__
#define __NAIVENETWORKHANDLER_H__

#include "NetworkHandler.h"

class NaiveNetworkHandler : public whytsoft::NetworkHandler
{
public:
    explicit NaiveNetworkHandler(short unsigned int socketId) : NetworkHandler{socketId} { }
    virtual void onNewConnection(long long unsigned int socketId) const override;
	virtual void onConnectionClosed(long long unsigned int socketId) const override;
    ~NaiveNetworkHandler() = default;
private:
};


#endif