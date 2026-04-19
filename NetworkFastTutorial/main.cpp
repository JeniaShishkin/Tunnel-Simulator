#include <iostream>

 #include "NetworkHandler.h"
 #include "NaiveNetworkHandler.h"

int main()
{

    std::cout << "I am running" << std::endl;
    NaiveNetworkHandler nh{9000};
    size_t socketId;
    std::string input;
    while(true)
    {
        nh.GetInput(&socketId, &input);
        std::cout << "received from " << socketId << " - " <<  input.length() << " bytes. Message: " << input << std::endl;
        std::string toSend = "thank you for sending " + input + "\n";
        nh.PutOutput(socketId, toSend);
    }


    return 0;
}