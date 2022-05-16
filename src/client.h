#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include<SDL2/SDL_net.h>
#include<cstring>

/*! \class client
    \brief class qui gère le client

    Dans cette classe on gère la reception/envoi de donnes pour le client et
    on fait l'affichage correspondant

*/
class client
{
private:
    IPaddress ip; //!< Server address
    TCPsocket sd; //!< Socket descriptor  
     
public:
    int quit, len;
    bool turn=true; //!< boolean pour la gestion du tour du joueur
    char buffer[512];//!< buffer pour la reception des donnes
    char buffer2[512];//!< buffer pour l'envoi des donnes 

    client();
    ~client();

    /*!
    * \brief Initialisation
    *\param arg1 ip du serveur
    *\param arg2 port
    * \details  permet la connexion avec le serveur et initialise le jeu pour le client
    */
    void clientInit(char *arg1, int arg2 );

    /*!
    * \brief Envoi
    * \details  permet l'envoi des donnes vers le serveur
    */
    void Send();

    /*!
    * \brief Receive
    * \details  permet la reception des donnes du serveur
    */
    void Receive();

    /*!
    * \brief Dialogue
    * \details  permet la comunication avec le serveur et l'affichage pour le client
    */
    void Communication(char *arg1);
    
    void Close();
};
#endif