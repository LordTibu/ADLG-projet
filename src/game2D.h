#ifndef GAME2D_H
#define GAME2D_H
#include "affichage2D.h"
#include "gameConsole.h"
#include<string>

class game2D
{
private:
    bool deployPhase = true;
    bool actUnit = true;
    bool playerTurn = true;
public:
    affichage2D * aff;
    gameConsole jeu;
    unsigned int lastTime = 0, currentTime;
    int Speed = 250;
    int input;
    int inputgame;
    bool isNOInit;
    int tailleG;
    bool cartSelect=false;
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