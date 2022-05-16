#ifndef SERVER_H
#define SERVER_H

#include<iostream>
#include<SDL2/SDL_net.h>
#include<cstring>
#include<string>

/*! \class server
    \brief class qui gère le server

   Cette class permet la creation d'un serveur
*/
class server
{
public:
    TCPsocket sd, csd1; //!< Socket descriptor, Client socket descriptor */
    IPaddress ip, *remoteIP;//!< Server address, Client address
    int quit, quit2, len;
    bool turn=true;
    char buffer1[512];
    char buffer2[512];
    
    server();
    ~server();

    /*!
    * \brief Initialisation
    * \details  permet l'initialisation d'un serveur et initialise le jeu pour le serveur
    */
    void serverInit();

    /*!
    * \brief Envoi
    * \details  permet l'envoi des donnes vers le client
    */
    void Send();

    /*!
    * \brief Receive
    * \details  permet la reception des donnes 
    */
    void Receive();

    /*!
    * \brief Dialogue
    * \details  permet la communication avec le client
    */
    void Communication();
    void Close();
};
#endif