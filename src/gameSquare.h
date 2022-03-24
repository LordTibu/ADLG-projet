#ifndef GAMESQUARE_H
#define GAMESQUARE_H
#include "unit.h"

/*! \class gameSquare
    \brief class qui gère une case

    Cette classe me chuâ los gvos
*/
class gameSquare
{
private:
    bool occupier;
    bool building;
    std::string terrain;
public:
    gameSquare();
    gameSquare(std::string terra, bool occupy, bool build);
    ~gameSquare();
    bool getOccupier();
    void occupy();
    void deOccupy();
    void afficherConsole() ;
};
#endif
