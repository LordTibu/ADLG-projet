#include "card.h"

class unit
{
private:
    card* cardIndex; // cardIndex relie l'unite a la carte qui lui donne ses stats et effets defaults
    unsigned int hp, atk;
    bool player1; // bool pour savoir auquel jouer appartient l'unite
public:
    unit();
    unit(card* Ncard, bool play);
    ~unit();
    void attackUnit(unit* ennemy);
    void battleUnit(unit* ennemy);
};