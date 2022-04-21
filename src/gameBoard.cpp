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

vec2 gameBoard::offToAx(int x, int y) const{
    vec2 v;
    v.q = y - (x - (x&1)) / 2; //Si x pair, x&1 = 0, sinon x&1 = 1
    v.r = x;
    return v;
}
vec2 gameBoard::axToOff(int q, int r) const{
    vec2 v;
    v.r = q + (r - (r&1)) / 2;
    v.q = r;
    return v;  // q holds the value for the X coord and s for Y coord
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
