#ifndef CARDLIB_H
#define CARDLIB_H

#include "card.h"
#include<vector>
#include<list>
#include<fstream>
#include<string>

/*! \class cardLib
    \brief class qui gère la librarie des cartes

    Cette classe me chuâ los gvos
*/
class cardLib
{
private:
    std::vector<card> cardLibrary;
public:
    cardLib();
    ~cardLib();
    void fillLibrary(const std::string & filename); //fonction qui remplit la librerie de toutes les cartes disponibles
    std::vector<card>& getLib();
    int getSize() const;
};
#endif
