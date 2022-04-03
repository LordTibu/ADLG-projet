#include "client.h"

client::client(){
    
}

client::~client(){
}

void client::clientInit( char *arg1, int arg2){
    if (SDLNet_Init() < 0) { 
        std::cerr << stderr <<"SDLNet_Init: " << SDLNet_GetError() <<"\n";
    }

    /* Resolve the host we are connecting to */ 
    if (SDLNet_ResolveHost(&ip, arg1, arg2) < 0) { 
        std::cerr << stderr <<"SDLNet_ResolveHost: " << SDLNet_GetError() << "\n";
    }
    
    /* Open a connection with the IP provided (listen on the host's port) */ 
    if (!(sd = SDLNet_TCP_Open(&ip))) { 
        std::cerr << stderr << "SDLNet_TCP_Open: " << SDLNet_GetError() << "\n"; 
    }
}

void client::Send(){
    len = strlen(buffer) + 1;
    if (SDLNet_TCP_Send(sd, (void *)buffer, len) < len) { 
        std::cout << stderr <<"SDLNet_TCP_Send: " << SDLNet_GetError() <<"\n"; 
    }
}

void client::Receive(){
    if ( SDLNet_TCP_Recv(sd,buffer2,512) > 0) { 
        std::cout << "Server say: " << buffer2 << std::endl;
                
        if(strcmp(buffer2, "quit") == 0) quit = 1;
    }
}

void client::Communication(char *arg1){
    quit = 0; 
    std::cout << "Connected to " <<arg1<<"\nexit or quit to disconnect\n";
    while (!quit) { 
        std::cout<< "------------------\n";
        if(turn){
            std::cout << "Write something:\n>";
            std::cin >> buffer;

            len = strlen(buffer) + 1; 
            Send();

            if(strcmp(buffer, "exit") == 0) quit = 1; 
            if(strcmp(buffer, "quit") == 0) quit = 1;
            
            turn = false; 
        }else{
            Receive();
            turn = true;     
        }
    }
}

void client::Close(){
    SDLNet_TCP_Close(sd); 
    SDLNet_Quit();
}

