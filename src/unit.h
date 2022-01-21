#include "cardLib.h"

class unit
{
private:
std::string unitName;
    card* cardIndex; // cardIndex relie l'unite a la carte qui lui donne ses stats et effets defaults
    unsigned int hp, atk, xpos, ypos; // les pos indiquent la position dans de le tableau du jeu
    bool player1; // bool pour savoir auquel jouer appartient l'unite
public:
    unit();
    unit(card& Ncard, bool play);
    ~unit();
    void attackUnit(unit* ennemy);
    void battleUnit(unit* ennemy);
    void afficherConsole() const;
    void afficherInitiales();
    void afficherPosition();
    void moveTo(unsigned int x, unsigned int y);
};