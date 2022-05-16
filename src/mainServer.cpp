#include "gameConsole.h"
using namespace std;

int main(void){
    gameConsole jeu;
    cout << "Esta compilando el archivo q es" << endl;
    jeu.gameInitServer(5, 5);
    
    jeu.gameUpdateNET();
    return 0;
}