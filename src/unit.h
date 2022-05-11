#ifndef UNIT_H
#define UNIT_H

#include "cardLib.h"

/*! \class unit
    \brief class qui gère l'unit

    Cette classe me chuâ los gvos
*/
class unit
{
private:
    std::string unitName;
    card* cardIndex; // cardIndex relie l'unite a la carte qui lui donne ses stats et effets defaults
    unsigned int hp, atk, ptr, xpos, ypos, movRange, atkRange; // les pos indiquent la position dans de le tableau du jeu
    bool player1, isChamp; // bool pour savoir auquel jouer appartient l'unite
public:
    unit();
    unit(card& Ncard, bool play);
    ~unit();

    unsigned int getX() const;
    unsigned int getY() const;
    std::string getName() const;
    bool isPlayers() const;

    bool isInRange(unsigned int x, unsigned int y) const;
    bool isInAtkRange(unsigned int x, unsigned int y) const;
    void attackUnit(unit &ennemy);
    void attackUnitNET(unit &ennemy);
    bool battleUnit(unit &ennemy); //returns true in case of a victory, false if not
    bool battleUnitNET(unit &ennemy);
    void afficherConsole() const;
    void afficherInitiales();
    void afficherPosition();
    bool moveTo(unsigned int x, unsigned int y);

    bool operator==(const unit &u);
};
#endif