#include "gameBoard.h"
using namespace std;

gameBoard::gameBoard(){
    dimx = dimy = 0;
    table = NULL;
}

gameBoard::gameBoard(unsigned int Ndimx, unsigned int Ndimy){
    dimx = Ndimx;
    dimy = Ndimy;
    table = new gameSquare[dimx*dimy];
}

gameBoard::~gameBoard(){
    if(table != NULL){
    delete[] table;
    table = NULL;
    }
}

void gameBoard::afficherConsole(){
    //bool alternate = false;
    if(table!=NULL){
        for(unsigned int i = 0; i < 5; i++){
            cout << "[ ";
            //if(alternate) {cout << "  ";}
            for(unsigned int j = 0; j < 5; j++){
                table[j * dimx + i].afficherConsole();
            }
            //alternate = !alternate;
            cout << "]" << endl;
        }
    }
}

gameSquare* gameBoard::getTable(){
    return table;
}