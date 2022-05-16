#include "gameConsole.h"
#include "deckBuilder.h"
using namespace std;

int main(void){
    gameConsole jeu;
    deckBuilder dBuilder;
    dBuilder.init();
    int input;
    string argv1;
    bool stay = true;

    while(stay){
        cout << "**************************" << endl;
        cout << "Bienvenu au menu principal" << endl;
        cout << "choisir le mode de jeu - 1 singleplayer, 2 multiplayer, 3 connect to server, 4. DeckBuilder, 0 close"<< endl;
        cout << "**************************" << endl;

        while(input < 0 || input > 4){
            cout<<"Introduire un input valide: "<<endl;
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

        if(input == 4){
            dBuilder.setStay(true);
            while(dBuilder.Stay()){
                dBuilder.run();
            }
        }

        if(input == 0){
            cout << "**************************" << endl;
            cout << "Closing Game..." << endl;
            cout << "  /~\\    ____________" << endl;
            cout << " C oo   | Goodbye... |" << endl;
            cout << " _( ^)   ------------" << endl;
            cout << "/   ~\\" << endl;
            stay = false;
        }
        input = -1;
    }
    return 0;
}