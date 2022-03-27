#include "gameConsole.h"
using namespace std;

int main(void){
    gameConsole jeu;
    cout << "Esta compilando el archivo q es" << endl;
    jeu.gameInit(5, 5);
    
    jeu.gameUpdateNET();
    
    cout << "SegFault after main" << endl;
    return 0;
}