#ifndef AFFICHAGE2D_H
#define AFFICHAGE2D_H

#include <SDL2/SDL.h>
#include <iostream>

class affichage2D
{
private:
    SDL_Window * window;
    SDL_Renderer * renderer;

public:
    //Rect de las casillas del menu
    SDL_Rect rectToDraw2;
    SDL_Rect rectToDraw1;
    SDL_Rect rectToDraw3;
    SDL_Rect rectToDraw4;

    SDL_Rect rectPlayer;

    SDL_Rect * cartes;
    SDL_Event event;
    
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    bool isMenu;
    bool isRun;
    bool isCreate;
    affichage2D();
    void init2D();
    void initdeck2D(int n);
    void menu2D();
    void erasemenu2D();
    void drawTable(int n);
    void drawDeck(int n);
    void drawGame(int n, int d);
    void clean2D();
    ~affichage2D();
};

#endif