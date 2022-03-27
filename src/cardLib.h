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
    void fillLibrary(const std::string & filename); // fonction qui remplit la librairie de toutes les cartes disponibles
    void saveToFile(const std::string & filename); // Sauvegarde la lib dans un fichier .txt
    void ajouterCarte(const card &c);
    void supprimerCarte(int index);
    std::vector<card>& getLib();
    void afficher() const;
    int getSize() const;
};
#endif
