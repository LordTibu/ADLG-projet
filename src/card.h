#ifndef CARD_H
#define CARD_H

#include<string>
#include<iostream>
#include<assert.h>

/*! \class card
    \brief class qui gère les cartes dans le jeu

    C'est les objets qui vont contenir les informations de base 
    pour tous les combattans du jeu.
*/
class card
{
private:
    std::string name; /** Nom du combattant (ou unit)*/
    std::string description; /** Description de l'unite, surtout esthetique*/
    int index, /** ID de la carte*/
        life,  /** Points de vie de la carte*/
        attack, /** Points de attaque de la carte*/
        protection, /** Points de protection (armor) de la carte*/
        movRange, /** Quantite des terrains que peut avancer l'unite en 1 tour de la carte*/
        atkRange, /** Distance d'attaque de l'unit*/
        isChamp; /** Bool pour savoir si c'est ou pas un Champion (joue le role du Roi au échecs*/
    friend class unit; /** Les unites ont access aux données des cartes pour utiliser ses stats*/
public:
    card();
    card(std::string nom, std::string Ndesc, unsigned int Nindex,
        unsigned int Nlife, unsigned int Nattack, unsigned int Nprotection,
        unsigned int nRange, unsigned int nAtkRange, bool champ);
    ~card();
    void afficherConsole() const;
    /** Fontion qui affiche les initiales de la carte*/
    void afficherInitiales() const;
    bool itsChamp() const;
    std::string getName() const;
    friend std::ostream& operator<<(std::ostream& os, card c);
};
#endif
