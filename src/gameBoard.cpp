#include "gameBoard.h"
using namespace std;

gameBoard::gameBoard(){
    dimx = dimy = 0;
    table = NULL;
}

gameBoard::gameBoard(unsigned int Ndimx, unsigned int Ndimy){
    dimx = Ndimx;
    dimy = Ndimy;
    table = new gameSquare[dimx * dimy];
    cout << "gameBoard created with x = " << dimx << " and y = " << dimy << endl;
}

gameBoard::~gameBoard(){
    if(table != NULL){
        delete[] table;
        table = NULL;
    }
    cout << "GameBoard succesfully destroyed" << endl;
}

void gameBoard::init(unsigned int x, unsigned int y){
    assert(table == NULL);
    dimx = x;
    dimy = y;
    table = new gameSquare[dimx * dimy];
    cout << "gameBoard created with x = " << dimx << " and y = " << dimy << endl;
}

void gameBoard::afficherConsole() const {
    //bool alternate = false;
    if(table!=NULL){
        cout << "dimensions: " << dimx << dimy << endl;
        cout << "***** TABLE *****" << endl;
        for(unsigned int i = 0; i < dimx; i++){
            cout << "[ ";
            //if(alternate) {cout << "  ";}
            for(unsigned int j = 0; j < dimy; j++){
                table[j * dimx + i].afficherConsole();
            }
            //alternate = !alternate;
            cout << "]" << endl;
        }
        cout << "***** TABLE *****" << endl;
        cout << endl;
    }
}

unsigned int gameBoard::getX() const{
    return dimx; 
}

unsigned int gameBoard::getY() const{
    return dimy; 
}

gameSquare* gameBoard::getTable(){
    return table;
}
