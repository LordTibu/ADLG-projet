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
    unit* occupier;
    unit* building;
    std::string terrain;
public:
    gameSquare();
    gameSquare(std::string terra, unit* occupy, unit* build);
    ~gameSquare();
    unit* getOccupier();
    void occupy(unit* Noccupier);
    void deOccupy();
    void afficherConsole() const;
};
#endif
