#include "gameSquare.h"

class gameBoard
{
private:
    unsigned int dimx, dimy;
    gameSquare* table;
public:
    gameBoard();
    gameBoard(unsigned int Ndimx, unsigned int Ndimy);
    ~gameBoard();
    void afficherConsole();
};
