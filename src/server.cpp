#include "server.h"

server::server(){
    
}

server::~server(){
}

void server::serverInit(){
    if (SDLNet_Init() < 0) {
        std::cerr<< stderr << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
    }

/* Resolving the host using NULL make network interface to listen */ 
    if (SDLNet_ResolveHost(&ip, NULL, 5000) < 0) { 
        std::cerr << stderr <<"SDLNet_ResolveHost: "<< SDLNet_GetError()<<std::endl; 
    }
/* Open a connection with the IP provided (listen on the host's port) */ 
    if (!(sd = SDLNet_TCP_Open(&ip))) { 
        std::cerr << stderr << "SDLNet_TCP_Open: " << SDLNet_GetError() <<std::endl; 
    }
    
}

void server::Send(){
    len = strlen(buffer2) + 1;
    if (SDLNet_TCP_Send(csd1, (void *)buffer2, len) < len) {
        std::cout << stderr <<"SDLNet_TCP_Send: " << SDLNet_GetError() <<"\n"; 
    }  
}

void server::Receive(){
    if (SDLNet_TCP_Recv(csd1, buffer1, 512) > 0) { 
        std::cout << "Client1 say: " << buffer1 << std::endl;
        /* Terminate this connection */
        if(strcmp(buffer1, "exit") == 0)  {
            quit2 = 1; 
            std::cout <<"Terminate connection\n"; 
        } 
    /* Quit the program */    
     if(strcmp(buffer1, "quit") == 0)  {
        quit2 = 1; 
        quit = 1; 
        std::cout<<"Quit program\n"; 
        }   
    }
}

void server::Communication(){
    quit = 0; 
    while (!quit) {
        /* This check the sd if there is a pending connection. * If there is one, accept that, and open a new socket for communicating */ 
        //First player
        if ((csd1 = SDLNet_TCP_Accept(sd)) ) { 
        /* Now we can communicate with the client using csd socket * sd will remain opened waiting other connections */

        /* Get the remote address */ 
            if ((remoteIP = SDLNet_TCP_GetPeerAddress(csd1))) 
            /* Print the address, converting in the host format */ 
           std::cout << "Host connected: " << SDLNet_Read32(&remoteIP->host) << SDLNet_Read16(&remoteIP->port) << std::endl;
            else std::cerr << stderr << "SDLNet_TCP_GetPeerAddress: " << SDLNet_GetError() << std::endl;
            
           /* SDLNet_TCP_Send(csd1, buffer2, strlen(buffer2)+1);*/
            quit2 = 0;  
            while (!quit2) { 
                std::cout<< "------------------\n";
                if(turn){
                    Receive();
                    turn = false;
                } else {

                    std::cout << "Admin Write something:\n>"; 
                    std::cin >> buffer2;
                    len = strlen(buffer2) + 1; 

                    Send();
                        /* Quit the program */    
                        if(strcmp(buffer2, "quit") == 0)  {
                            quit2 = 1; 
                            quit = 1; 
                            std::cout<<"Quit program\n"; 
                        } 
                        
                    turn = true; 
                }
            }
            
         /* Close the client socket */ 
            SDLNet_TCP_Close(csd1); 
        } 
    }
}

/*void server::WriteMove(const char move){
    buffer2 = move;
}*/

void server::Close(){
    SDLNet_TCP_Close(sd); 
    SDLNet_Quit();
}