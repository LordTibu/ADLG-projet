#include "unit.h"

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
    void occupySquare();
};
