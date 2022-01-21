#include "card.h"
#include<vector>

class cardLib
{
private:
    std::vector<card> cardLibrary;
public:
    cardLib();
    ~cardLib();
    void fillLibrary(); //fonction qui remplit la librerie de toutes les cartes disponibles
    std::vector<card>& getLib();
};
