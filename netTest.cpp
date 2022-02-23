#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<string.h>
#include<string>

int main(void){
    //Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0); //Creating a listening socket for the server
    if(listening == -1){
        std::cerr << "Error while creating listening socket\n";
        return -1;
    }
    //Bind it to an IP and Port 
    sockaddr_in skAddr; //Creating a Socket address
    skAddr.sin_family = AF_INET;
    skAddr.sin_port = htons(54001); //We give a Port to use (htons is to convert the bytes for any machine)
    inet_pton(AF_INET, "172.28.27.106", &skAddr.sin_addr); //We give it an IP adress (127.0.0.1 for localhost)
    if(bind(listening, (struct sockaddr*) &skAddr, sizeof(skAddr)) < 0){ //Actual binding
        std::cerr << "Error at binding IP/port\n";
        return -2;
    }
    //Setting the socket to listen for new client connexions
    if(listen(listening, 5) < 0){ //it will allow a queue of max 5 clients trying to connect
        std::cerr << "Error at listening\n";
        return -3;
    }
    else std::cout << "Server socket started and listening for connections\n";
    //Setting the socket to accept a new connexion from a client if one happens
    sockaddr_in client;
    socklen_t addrLenght = (socklen_t)sizeof(client);
    int client_socket = accept(listening, (struct sockaddr*)&client, &addrLenght);
    if(client_socket < 0){
        std::cerr << "Error at accept\n";
        return -4;
    }
    //Getting the IP/port info from the client connexion
    char host[NI_MAXHOST] = {0};
    char svc[NI_MAXSERV] = {0};
    int result = getnameinfo((sockaddr*)&client, addrLenght, host, NI_MAXHOST, svc, NI_MAXSERV, 0);
    if(result){
        std::cout << host << "connected on: " << svc << std::endl;
    }
    else{
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << "connected on: " << ntohs(client.sin_port) << std::endl;
    }
    //Reading client message
    close(listening);
    char buffer[1024] = {0};
    int valread;
    bool clientStay = true;

    while(clientStay){
    valread = recv(client_socket, buffer, 1024, 0);
    if(valread == -1){
        std::cout << "Error at reading message from client\n";
    }
    if(valread == 0){
        std::cout << "Client disconnected\n";
        clientStay = false;
    }
    std::cout << "Received: " << std::string(buffer, 0, valread) << std::endl;
    send(client_socket, buffer, valread + 1, 0);
    }
    close(client_socket);
    return 0;
}