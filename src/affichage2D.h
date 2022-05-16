#ifndef AFFICHAGE2D_H
#define AFFICHAGE2D_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "unit.h"


/*! \class affichage2D
    \brief class qui gère l'affichage

    Dans cette classe on gère l'affichage avec SDL2 du jeu

*/
class affichage2D
{
private:
    SDL_Window * window;
    SDL_Renderer * renderer;
    friend class game2D;
    SDL_Texture * Menu1;//!<Texture pour le menu
    SDL_Texture * Menu2;//!<Texture pour le menu
    SDL_Texture * Menu3;//!<Texture pour le menu
    SDL_Texture * Menu4;//!<Texture pour le menu
    SDL_Texture * backmenu;//!<Texture pour le menu

    SDL_Texture * backgame;//!<Texture pour le jeu
    SDL_Texture * backcard;//!<Texture pour le jeu
    SDL_Texture * cardselect;//!<Texture pour le jeu

    SDL_Texture * jesucristo;//!<Texture 
    SDL_Texture * soldat;//!<Texture 
    SDL_Texture * archer;//!<Texture 
    SDL_Texture * peasant;//!<Texture 
    SDL_Texture * shinobi;//!<Texture 
    SDL_Texture * samurai;//!<Texture

    SDL_Texture * square;//!<Texture pour le jeu

    SDL_Texture * end;//!<Texture pour le jeu

public:
   
    SDL_Rect rectToDraw2;//!<Position des buttons du menu
    SDL_Rect rectToDraw1;//!<Position des buttons du menu
    SDL_Rect rectToDraw3;//!<Position des buttons du menu
    SDL_Rect rectToDraw4;//!<Position des buttons du menu

    SDL_Rect rectPlayer;//!<Position de la couleur du joueur

    SDL_Rect ** table;//!<tableau de la position des case de la grille
    SDL_Rect * cartes;//!<tableau des cartes
    SDL_Rect * PlayerUnits;//!<tableau des unites du Joueur 1
    SDL_Rect * EnnemyUnits;//!<tableau des unites du Joueur 2
    SDL_Event event;
    
    std::string nameCard;//!<nom de la carte a afficher

    bool cardDisplayed = false;
    int posx, posy;
    int SCREEN_WIDTH, SCREEN_HEIGHT;//!<taille de l'ecran largeur x hauteur
    bool isMenu=true;
    bool isRun;
    bool isCreate;
    int idCard=0;
    affichage2D();
    /*!
    * \brief Initialisation
    * \details  permet la initialisation de SDL2
    */
    void init2D();

    /*!
    * \brief Initialisation
    * \details  permet la initialisation des textures et des buttons
    */
    void initdeck2D(int n, int d);

    /*!
    * \brief menu
    * \details  permet l'affichage du menu
    */
    void menu2D();

    /*!
    * \brief menu
    * \details  permet d'effacer le menu
    */
    void erasemenu2D();

    /*!
    * \brief Dessiner grille
    *@param n taille de la grille
    * \details  permet l'affichage de la grille
    */
    void drawTable(int n);

    /*!
    * \brief Dessiner le deck du joueur
    *@param n taille du deck
    *@param player boolean qui indique quelle joueur est entrain de joueur
    * \details  permet l'affichage du deck
    */
    void drawDeck(int n, bool player);

    /*!
    * \brief Dessine tout le jeu
    * \details  cette fonction contient toutes les autres fonctions d'affichage
    */
    void drawGame(int n, int d,bool cart,bool player,std::vector<unit> UnitsPlayer, std::vector<unit> UnitsEnnemy);

    /*!
    * \brief Dessine tout le game over
    * \details  cette fonction affiche le game over
    */
    void drawEnd();

    /*!
    * \brief Dessiner tous les units du jouer
    *@param Units vecteur de unit 
    *@param player boolean qui indique quelle joueur est entrain de joueur
    * \details  permet l'affichage de tous les units du jouer
    */
    void drawallunits(std::vector<unit> Units, bool player);

    /*!
    * \brief Dessiner une card
    *@param cart boolean pour afficher une carte
    * \details  permet l'affichage en grand a gauche de la carte selectionner
    */
    void drawCart(bool cart);

    /*!
    * \brief Dessine une unit
    *@param posx position x dans la grille
    *@param posy position y dans la grille
    * \details  permet l'affichage d'une unit dans la grille
    */
    void drawUnit(int posx, int posy);
    void clean2D(int n);
    ~affichage2D();
};

#endif