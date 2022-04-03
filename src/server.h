#ifndef SERVER_H
#define SERVER_H

#include<iostream>
#include<SDL/SDL_net.h>
#include<cstring>
#include<string>

/*! \class server
    \brief class qui gère le server

    Cette classe me chuâ los gvos
*/
class server
{
public:
    TCPsocket sd, csd1; /* Socket descriptor, Client socket descriptor */
    IPaddress ip, *remoteIP;
    int quit, quit2, len;
    bool turn=true;
    char buffer1[512];
    char buffer2[512];
    
    server();
    ~server();
    void serverInit();
    void Send();
    void Receive();
    void WriteMove(const char move);
    void Communication();
    void Close();
};
#endif