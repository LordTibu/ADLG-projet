#ifndef GAMESQUARE_H
#define GAMESQUARE_H
#include "unit.h"

/*! \class gameSquare
    \brief Classe qui gere les cases de jeu
    
*/
struct vec2{
    int q, r;
};

class gameSquare
{
private:
    bool occupied; /** Si la case est occupé par une unite quelconque (utile pour affichage texte)*/
    std::string terrain;
    std::string unitName; /** Nom de l'unit qui occupe la case*/
public:
    gameSquare();
    gameSquare(std::string terra, bool occupy);
    ~gameSquare();
    bool isOccupied() const;
    /** Occupe la case
     * @param unit unit qui maintenant occupe la case
    */
    void occupy(const unit& u);
    /** Deoccupe la case*/
    void deOccupy();
    /** Affiche le case en version console*/
    void afficherConsole();
    /** Change unitName 
     * @param s string avec le nom de l'unite qui occupe la case
    */
    void setName(const std::string& s);
};
#endif
