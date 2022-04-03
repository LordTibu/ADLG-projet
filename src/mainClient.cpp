#include"gameConsole.h"
using namespace std;

int main() {
    gameConsole jeu;
    cout << "Esta compilando el archivo q es" << endl;
    string argv1;
    cin>>argv1;

    jeu.gameInitClient(5,5,(char*)argv1.c_str(),5000);
    jeu.gameUpdateNETClient();

    cout << "SegFault after main" << endl;
    return 0; 
}