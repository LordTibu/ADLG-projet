#ifndef AFFICHAGE2D_H
#define AFFICHAGE2D_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "unit.h"

class affichage2D
{
private:
    SDL_Window * window;
    SDL_Renderer * renderer;
    friend class game2D;
    SDL_Texture * Menu1;
    SDL_Texture * Menu2;
    SDL_Texture * Menu3;
    SDL_Texture * Menu4;
    SDL_Texture * backmenu;

    SDL_Texture * backgame;
    SDL_Texture * backcard;
    SDL_Texture * cardselect;

    SDL_Texture * jesucristo;
    SDL_Texture * soldat;
    SDL_Texture * archer;
    SDL_Texture * peasant;
    SDL_Texture * shinobi;
    SDL_Texture * samurai;

    SDL_Texture * square;

public:
    //Rect de las casillas del menu
    SDL_Rect rectToDraw2;
    SDL_Rect rectToDraw1;
    SDL_Rect rectToDraw3;
    SDL_Rect rectToDraw4;

    SDL_Rect rectPlayer;

    SDL_Rect ** table;
    SDL_Rect * cartes;
    SDL_Rect * PlayerUnits;
    SDL_Rect * EnnemyUnits;
    SDL_Event event;
    
    std::string nameCard;

    bool cardDisplayed = false;
    int posx, posy;
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    bool isMenu=true;
    bool isRun;
    bool isCreate;
    int idCard=0;
    affichage2D();
    void init2D();
    void initdeck2D(int n, int d);
    void menu2D();
    void erasemenu2D();
    void inittable2D(int n);
    void drawTable(int n);
    void drawDeck(int n, bool player);
    void drawGame(int n, int d,bool cart,bool player,std::vector<unit> UnitsPlayer, std::vector<unit> UnitsEnnemy);
    void drawallunits(std::vector<unit> Units, bool player);
    void drawCart(bool cart);
    void drawUnit(int posx, int posy);
    void clean2D(int n);
    ~affichage2D();
};

#endif