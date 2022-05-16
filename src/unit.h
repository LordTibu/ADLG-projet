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
<<<<<<< HEAD
    std::string unitName; /** Nom de l'unit*/
    card* cardIndex; /** Pointe vers la carte a partir de laquelle est genere l'unit*/
    int hp, /** Points de vie actuels de l'unit*/
        atk, /** Points d'attaque actuels de l'unit*/
        ptr, /** Points de protection courants de l'unit*/
        xpos, /** Position x actuelle de l'unit*/
        ypos, /** Position y actuelle de l'unit*/
        movRange, /** Combien de cases peut avancer l'unit actuellement*/
        atkRange; /** Depuis combien de cases de distance l'unit peut attaquer une autre*/
    bool player1, /** Identifie a quel joueur appartient l'unit*/
        isChamp, /**Identifie si l'unit est un Champion*/
        canAttack, /**Indique si l'unit peut attaquer une autre*/
        canMove; /** Indique si l'unit peut bouger*/
    std::vector<statusInfo> appliedStatus; /** Effets d'etat qui souffre l'unit*/
    statusInfo attackStatus; /** Effet d'etat que l'unit peut apliquer à d'autres en combattant*/
=======
    std::string unitName;
    card* cardIndex; // cardIndex relie l'unite a la carte qui lui donne ses stats et effets defaults
    int hp, atk, ptr, xpos, ypos, movRange, atkRange; // les pos indiquent la position dans de le tableau du jeu
    bool player1, isChamp, canAttack, canMove; // bool pour savoir auquel jouer appartient l'unite
    std::vector<statusInfo> appliedStatus;

>>>>>>> 6b2c50a84b9a0b3ebf95ca5cfe7deb811f66ffaf
public:
    unit();
    unit(card& Ncard, bool play);
    ~unit();

    int getX() const;
    int getY() const;
    int getAtkRange() const;
    std::string getName() const;
    bool isPlayers() const;
    /** Verifie si la position est dans le rang de mouvement de l'unit
     * @param x coord. x de la position a verifier
     * @param y coord. y de la position a verifier
     * @return true si la position est dans le rang, false sinon
    */
    bool isInRange(int x, int y) const;
    /** Verifie si la position est dans le rang de d'attaque de l'unit
     * @param x coord. x de la position a verifier
     * @param y coord. y de la position a verifier
     * @return true si la position est dans le rang, false sinon
    */
    bool isInAtkRange(int x, int y) const;
    /** Attaque une unit ennemie en version locale
     * @param ennemy unit ennemie laquelle ataquer
    */
    void attackUnit(unit &ennemy);
    /** Attaque une unit ennemie en version LAN
     * @param ennemy unit ennemie laquelle ataquer
    */
    void attackUnitNET(unit &ennemy);
    /** Simule une bataille entre unit en version locale (utilise attackUnit)
     * @param ennemy unit ennemie laquelle ataquer
     * @return boolean
    */
    bool battleUnit(unit &ennemy);
    /** Simule une bataille entre unit en version LAN
     * @param ennemy unit ennemie laquelle ataquer
    */
    bool battleUnitNET(unit &ennemy);
    /** Affiche les informations en detail de l'unit*/
    void afficherConsole() const;
    /** Affiche les initiales de l'unit (utilisé pour les afficher dans le tableau de jeu)*/
    void afficherInitiales();
    /** Affiche la position de l'unit*/
    void afficherPosition();
    /** MaJ les stats de l'unit en fonction d'un effet d'etat
     * @param s status selon lequel MaJ les stats
    */
    void applyStatus(const status& s);
    /** Ajoute un effet d'etat au vector de l'unite
     * @param s status a ajouter
    */
    void addAppliedStatus(const statusInfo& s);
    bool itsChamp() const;
    /** Taille de appliedStatus
     * @returns appliedStatus.size()
    */
    int getAppliedSize() const;
    statusInfo& getAppliedStatus(int index);
    void eraseAppliedStatus(int index);
    /** Deplace l'unite a la position indiqué
     * @param x coord. x de la position
     * @param y coord. y de la position
     * @return true si le deplacement a marchée, false si la position est en dehors du rang de deplacement
    */
    bool moveTo(int x, int y);
    /** Force la position de l'unite a la position indique
     * @param x coord. x de la position
     * @param y coord. y de la position 
    */
    void setTo(int x, int y);

    bool operator==(const unit &u);
};
#endif