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

    SDL_Event event;
    
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    bool isRun;
    affichage2D();
    void init2D();
    void menu2D();
    void clean2D();
    ~affichage2D();
};

#endif