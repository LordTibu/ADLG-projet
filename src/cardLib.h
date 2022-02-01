#ifndef CARDLIB_H
#define CARDLIB_H

#include "card.h"
#include<list>

class cardLib
{
private:
    std::list<card> cardLibrary;
public:
    cardLib();
    ~cardLib();
    void fillLibrary(); //fonction qui remplit la librerie de toutes les cartes disponibles
    std::list<card>& getLib();
};
#endif
