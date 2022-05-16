#ifndef GAME2D_H
#define GAME2D_H
#include "affichage2D.h"
#include "gameConsole.h"
#include<string>

class game2D
{
private:
    bool deployPhase = true;
    bool actUnit = true;
    bool playerTurn = true;
public:
    affichage2D * aff;
    gameConsole jeu;
    int input;//!<input pour l'extraction des clicks pour le menu
    const int FPS=60;//!<limitation de l'affichage
    const int frameDelay=1000/FPS;//!<limitation de l'affichage
    Uint32 frameStart;//!<limitation de l'affichage
    int frameTime;//!<limitation de l'affichage
    int inputgame;//!<input pour l'extraction des clicks pour le jeu
    bool isNOInit;//!<bool pour l'initialisation de jeu
    int tailleG;//!<taille de la grille
    bool cartSelect=false;
    bool isUnits = false;
    game2D();

    /*!
    * \brief Initialisation
    * \details initialise le jeu en 2D
    */
    void initgame2D();

    /*!
    * \brief update
    * \details contient tout correspondant a l'affichage et la gestion des buttons
    */
    void updategame2D();

    /*!
    * \brief menu buttons
    * \details gestion de tous les buttons du menu
    */
    void menu2D();

    /*!
    * \brief jeu local
    * \details gestion de la version 2D du jeu en local
    */
    void local();

    /*!
    * \brief jeu multiplayer serveur
    * \details 
    */
    void mulplayerserver();

    /*!
    * \brief type de jeu
    * \details permet de lancer un des 3 modes de jeu selon la valeur de input
    */
    void typegame();

    /*!
    * \brief jeu multiplayer connexion
    * \details
    */
    void connectmultiplayer();
    void cleangame2D();
    ~game2D();
};

#endif