#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gameSquare.h"

/*! \class gameBoard
    \brief Classe qui gere le tableau de Jeu

    Elle contient le tableau de jeu et mets a jour ses cases
*/
class gameBoard
{
private:
    int dimx, /** Dimension x du tableu de jeu*/
        dimy; /** Dimension y du tableu de jeu*/
    gameSquare* table; /** Tableau contenant les cases du jeu*/
public:
    gameBoard();
    gameBoard(unsigned int Ndimx, unsigned int Ndimy);
    ~gameBoard();
    vec2 offToAx(int x, int y) const;
    vec2 axToOff(int q, int s) const;
    void init(unsigned int x, unsigned int y);
    void afficherConsole() const;
    gameSquare& operator[](int index);
    int getX() const;
    int getY() const;
    gameSquare* getTable();
};
#endif
