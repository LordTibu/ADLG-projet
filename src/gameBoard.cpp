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
    delete[] table;
    table = NULL;
}

void gameBoard::afficherConsole(){
    if(table!=NULL){
        for(unsigned int i = 0; i < 5; i++){
            cout << "[ ";
            for(unsigned int j = 0; j < 5; j++){
                cout << "index tab en lisant: " << j * dimx + i << endl;
                if(table[j * dimx + i].getOccupier() == NULL){
                    cout << "# ";
                }
                else {table[j * dimx + i].getOccupier()->afficherInitiales(); cout << " ";}
            }
            cout << "]" << endl;
        }
    }
}

gameSquare* gameBoard::getTable(){
    return table;
}