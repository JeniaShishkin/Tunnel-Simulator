#ifndef __NAIVENETWORKHANDLER_H__
#define __NAIVENETWORKHANDLER_H__

#include "NetworkHandler.h"

class NaiveNetworkHandler : public whytsoft::NetworkHandler
{
public:
    explicit NaiveNetworkHandler(size_t socketId) : NetworkHandler{socketId} { }
    virtual void onNewConnection(size_t socketId) const override;
	virtual void onConnectionClosed(size_t socketId) const override;
    ~NaiveNetworkHandler() = default;
private:
};


#endif