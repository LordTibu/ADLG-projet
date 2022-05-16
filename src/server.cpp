#include "server.h"

server::server(){
    
}

server::~server(){
}

void server::serverInit(){
    if (SDLNet_Init() < 0) {
        std::cerr<< stderr << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
    }

    if (SDLNet_ResolveHost(&ip, NULL, 5000) < 0) { 
        std::cerr << stderr <<"SDLNet_ResolveHost: "<< SDLNet_GetError()<<std::endl; 
    }
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
        if(strcmp(buffer1, "exit") == 0)  {
            quit2 = 1; 
            std::cout <<"Terminate connection\n"; 
        } 
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
        //First player
        if ((csd1 = SDLNet_TCP_Accept(sd)) ) { 

            if ((remoteIP = SDLNet_TCP_GetPeerAddress(csd1))) 
           std::cout << "Host connected: " << SDLNet_Read32(&remoteIP->host) << SDLNet_Read16(&remoteIP->port) << std::endl;
            else std::cerr << stderr << "SDLNet_TCP_GetPeerAddress: " << SDLNet_GetError() << std::endl;
            
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
                        if(strcmp(buffer2, "quit") == 0)  {
                            quit2 = 1; 
                            quit = 1; 
                            std::cout<<"Quit program\n"; 
                        } 
                        
                    turn = true; 
                }
            }
            
            SDLNet_TCP_Close(csd1); 
        } 
    }
}


void server::Close(){
    SDLNet_TCP_Close(csd1); 
    SDLNet_TCP_Close(sd); 
    SDLNet_Quit();
}