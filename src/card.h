#ifndef CARD_H
#define CARD_H

#include<string>
#include<iostream>
#include<assert.h>

/*! \class card
    \brief class qui gère les cards

    Cette classe me chuâ los gvos
*/
class card
{
private:
    std::string name, description;
    unsigned int index, life, attack, protection, movRange, atkRange, isChamp;
    friend class unit; // Les unites ont access aux données des cartes pour utiliser ses stats
public:
    card();
    card(std::string nom, std::string Ndesc, unsigned int Nindex, unsigned int Nlife, unsigned int Nattack, unsigned int Nprotection, 
        unsigned int nRange, unsigned int nAtkRange, bool champ);
    ~card();
    void afficherConsole() const;
    void afficherInitiales() const;
    bool itsChamp() const;
    std::string getName() const;
    friend std::ostream& operator<<(std::ostream& os, card c);
};
#endif
