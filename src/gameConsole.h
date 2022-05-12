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
    std::vector<card> lib, xd; //To acces the lib inside defaultPieces
    //defaultPieces.fillLibrary();
    //list<card>& lib = defaultPieces.getLib();
    std::vector<unit> playerDeck;
    std::vector<unit> playerUnits;
    std::vector<unit> ennemyDeck; //cartes
    std::vector<unit> ennemyUnits; //unites de combat
    server sv;
    client cl;
public:
    gameConsole();
    ~gameConsole();
    std::vector<unit> getplayerdeck() const;
    std::vector<unit> getplayerunits() const;
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
    bool Stay();
};
#endif