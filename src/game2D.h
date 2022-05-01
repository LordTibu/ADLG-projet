#ifndef GAME2D_H
#define GAME2D_H
#include "affichage2D.h"
#include "gameConsole.h"
#include<string>

class game2D
{
public:
    affichage2D * aff;
    gameConsole jeu;
    int input;
    bool isNOInit;
    int tailleG;
    game2D();
    void initgame2D();
    void updategame2D();
    void menu2D();
    void local();
    void mulplayerserver();
    void typegame();
    void connectmultiplayer();
    void cleangame2D();
    ~game2D();
};

#endif