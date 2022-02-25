#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gameSquare.h"

/*! \class gameBoard
    \brief class qui gère le board

    Cette classe me chuâ los gvos
*/
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
    gameSquare* getTable();
};
#endif
