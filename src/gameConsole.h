#ifndef GAMECONSOLE_H
#define GAMECONSOLE_H

#include"gameBoard.h"

/*! \class gameConsole
    \brief class qui gère le jeu en console

    Cette classe me chuâ los gvos
*/
class gameConsole
{
private:
    unsigned int xmove, ymove;
    int input;
    bool stay = true;
    bool deployPhase = true;
    bool actUnit = true;
    bool playerTurn = true;
    unsigned int dim = 5;
    unit* easeUnit; // ptr pour faire plus lisibles les operations
    gameBoard GB;
    cardLib defaultPieces;
    //defaultPieces.fillLibrary();
    //list<card>& lib = defaultPieces.getLib();
    std::list<unit> playerDeck;
    std::list<unit> playerUnits;
    std::list<unit> ennemyDeck;
    std::list<unit> ennemyUnits;
    std::list<unit>* userDeck;  //ptrs pour condenser la taille du code
    std::list<unit>* userUnits;
public:
    gameConsole();
    ~gameConsole();
    void gameInit(unsigned int xdim, unsigned int ydim);
    void gameUpdate();
    void gameHandleEvents();
    bool Stay();
};
#endif