#include "cardLib.h"
using namespace std;

cardLib::cardLib() {}
cardLib::~cardLib() {}

void cardLib::fillLibrary(){
    cardLibrary.push_back(card("soldat", "", 1, 2, 2));
    cardLibrary.push_back(card("archer", "", 2, 1, 1)); // ranged
    cardLibrary.push_back(card("peasant", "", 3, 1, 1));
    cardLibrary.push_back(card("shinobi", "", 4, 1, 3)); // assansins (possible bonus later in dev.)
    cardLibrary.push_back(card("samurai", "", 5, 3, 2));
}

std::vector<card>& cardLib::getLib(){
    return cardLibrary;
}