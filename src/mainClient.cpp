#include"gameConsole.h"
using namespace std;

int main(int argc, char **argv) {
    gameConsole jeu;
    cout << "Esta compilando el archivo q es" << endl;
    jeu.gameInitClient(5,5,argv[1],argv[2]);
    jeu.gameUpdateNETClient();

    cout << "SegFault after main" << endl;
    return 0; 
}