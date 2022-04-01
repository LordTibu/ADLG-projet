#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include<SDL/SDL_net.h>
#include<cstring>

/*! \class client
    \brief class qui gère le client

    Cette classe me chuâ los gvos
*/
class client
{
private:
    IPaddress ip; /* Server address */ 
    TCPsocket sd; /* Socket descriptor */ 
     
public:
    int quit, len;
    bool turn=true; 
    char buffer[512];
    char buffer2[512];

    client();
    ~client();
    void clientInit(char *arg1, char *arg2 );
    void Send();
    void Receive();
    void Communication(char *arg1);
    void Close();
};
#endif