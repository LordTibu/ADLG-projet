#ifndef AFFICHAGE2D_H
#define AFFICHAGE2D_H

#include <SDL2/SDL.h>
#include <iostream>

class affichage2D
{
private:
    SDL_Window * window;
    SDL_Renderer * renderer;
    friend class game2D;

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
    
    bool cardDisplayed = false;
    int posx, posy;
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    bool isMenu;
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
    void drawGame(int n, int d,bool cart,bool player);
    void drawCart(bool cart);
    void drawUnit(int posx, int posy);
    void clean2D(int n);
    ~affichage2D();
};

#endif