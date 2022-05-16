#ifndef CARDLIB_H
#define CARDLIB_H

#include "card.h"
#include<vector>
#include<list>
#include<fstream>
#include<string>

/*! \class cardLib
    \brief class qui gère la librarie des cartes

    Dans d'autres mots cette clase est un Deck de cartes,
    les cartes son organisées dans un vector.
*/
class cardLib
{
private:
    std::vector<card> cardLibrary; /** Vector qui contient les cartes dans le deck (ou librarie)*/
public:
    cardLib();
    ~cardLib();
    /**Remplit le vector avec les donnes d'un fichier .txt contenant les descriptions des cartes */
    void fillLibrary(const std::string & filename);
    /** Sauvegarde le Deck dans un fichier .txt,
     * Utilisée pour que l'utilisateur puissé créer son propre deck de cartes
     */
    void saveToFile(const std::string & filename);
    /** Ajoute une carte dans le vector */
    void ajouterCarte(const card &c);
    /** Supprime une carte du vector */
    void supprimerCarte(int index);
    /** On ne parle pas de cette fonction
     * C'est un memento d'un temps plus noir
    */
    std::vector<card>& getLib();
    /** Acces direct au vector de cartes
     * @param index index à acceder dans le vector
     * @return reference a la carte chez cardLibrary[index]
    */
    card& operator[](int index);
    /** Affiche les cartes dans la console*/
    void afficher() const;
    /** Trie le vector selon le nom des cartes (ordre ascendant)*/
    void sortD();
    /** @return si il y a un champion dans le vector*/
    bool hasChamp() const;
    /** @return si il y a un champion dans le vector, retourne son index*/
    int getChampIndex() const;
    /** @return taille du vector*/
    int getSize() const;
};
#endif
