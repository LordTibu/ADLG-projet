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
    unsigned int hp, atk, ptr, xpos, ypos; // les pos indiquent la position dans de le tableau du jeu
    bool player1; // bool pour savoir auquel jouer appartient l'unite
public:
    unit();
    unit(card& Ncard, bool play);
    ~unit();

    unsigned int getX() const;
    unsigned int getY() const;
    bool isPlayers() const;


    void attackUnit(unit* ennemy);
    bool battleUnit(unit* ennemy); //returns true in case of a victory, false if not
    void afficherConsole() const;
    void afficherInitiales();
    void afficherPosition();
    void moveTo(unsigned int x, unsigned int y);

    bool operator==(const unit &u);
};
#endif