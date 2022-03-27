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
    std::string tableLine; // Utile pour afficher le tableu + unites
    unit easeUnit; // ptr pour faire plus lisibles les operations
    gameBoard GB;
    cardLib defaultPieces;
    std::vector<card> lib; //To acces the lib inside defaultPieces
    //defaultPieces.fillLibrary();
    //list<card>& lib = defaultPieces.getLib();
    std::vector<unit> playerDeck;
    std::vector<unit> playerUnits;
    std::vector<unit> ennemyDeck;
    std::vector<unit> ennemyUnits;
public:
    gameConsole();
    ~gameConsole();
    void gameInit(unsigned int xdim, unsigned int ydim);
    void gameUpdate();
    void gameAfficher();
    void gameHandleEvents();
    bool Stay();
};
#endif