#ifndef GAMECONSOLE_H
#define GAMECONSOLE_H

#include"gameBoard.h"
#include"server.h"
#include"client.h"

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
    cardLib playerDeck;
    std::vector<unit> playerUnits;
    cardLib ennemyDeck; //cartes
    std::vector<unit> ennemyUnits; //unites de combat
    server sv;
    client cl;
    friend class game2D;
public:
    gameConsole();
    ~gameConsole();
    bool getdeployphase() const;
    void gameInit(unsigned int xdim, unsigned int ydim);
    void gameInitServer(unsigned int xdim, unsigned int ydim);
    void gameInitClient(unsigned int xdim, unsigned int ydim, char *arg1, int arg2);
    void gameUpdate();
    void gameUpdateNET();
    void gameUpdateNETClient();
    void gameUpdateNO();
    void gameUpdateNETNO();
    void gameUpdateNETClientNO();
    void gameAfficher();
    void gameHandleEvents();
    void gameEnd();
    void deployUnitPlayer(int input);
    void deployUnitEnnemy(int input);
    void moveUnitPlayer(int input);
    void moveUnitEnnemy(int input);
    void attackByPlayer(int input);
    void attackByEnnemy(int input);
    void checkForGameEnd();
    void triggerVictory(bool player);
    void triggerDraw();
    bool Stay();
};
#endif