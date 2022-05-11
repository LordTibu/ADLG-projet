#include "gameConsole.h"
using namespace std;

int main(void){
    gameConsole jeu;
    int input;
    string argv1;
    cout << "choisir le mode de jeu - 1 singleplayer, 2 multiplayer, 3 connect to server, 0 close"<<endl;
    //cout << "Esta compilando el archivo q es" << endl;
    cin >> input;

    while(input < 0 || input > 3){
        cout<<"input non reconnu, svp ressayer :"<<endl;
        cin>>input;
    }

    if(input == 1){
        jeu.gameInit(5, 5);
        while(jeu.Stay()){
            jeu.gameUpdate();
        }
    }
    
    if(input ==2){
        jeu.gameInitServer(5, 5);
        jeu.gameUpdateNET();
    }
    
    if(input==3){
        cout << "saisir l'ip du server :";
        cin>>argv1;

        jeu.gameInitClient(5,5,(char*)argv1.c_str(),5000);
        jeu.gameUpdateNETClient();
    }

    if(input==0){
        cout <<"Close";
    }
    return 0;
}