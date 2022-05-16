#ifndef UNIT_H
#define UNIT_H

#include "cardLib.h"
#include "statusCodex.h"

/*! \class unit
    \brief class qui gère l'unit

    Cette classe me chuâ los gvos
*/
class unit
{
private:
    std::string unitName;
    card* cardIndex; // cardIndex relie l'unite a la carte qui lui donne ses stats et effets defaults
    int hp, atk, ptr, xpos, ypos, movRange, atkRange; // les pos indiquent la position dans de le tableau du jeu
    bool player1, isChamp, canAttack, canMove; // bool pour savoir auquel jouer appartient l'unite
    std::vector<statusInfo> appliedStatus;
public:
    unit();
    unit(card& Ncard, bool play);
    ~unit();

    int getX() const;
    int getY() const;
    std::string getName() const;
    bool isPlayers() const;

    bool isInRange(int x, int y) const;
    bool isInAtkRange(int x, int y) const;
    void attackUnit(unit &ennemy);
    void attackUnitNET(unit &ennemy);
    bool battleUnit(unit &ennemy); //returns true in case of a victory, false if not
    bool battleUnitNET(unit &ennemy);
    void afficherConsole() const;
    void afficherInitiales();
    void afficherPosition();
    void applyStatus(const status& s);
    bool itsChamp() const;
    int getAppliedSize() const;
    statusInfo& getAppliedStatus(int index);
    void eraseAppliedStatus(int index);
    bool moveTo(unsigned int x, unsigned int y);
    void setTo(int x, int y);

    bool operator==(const unit &u);
};
#endif