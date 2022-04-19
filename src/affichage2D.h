#ifndef AFFICHAGE2D_H
#define AFFICHAGE2D_H

#include <SDL2/SDL.h>
#include <iostream>

class affichage2D
{
private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
public:
    SDL_Window* window;
    SDL_Surface* screenSurface;

    affichage2D();
    void affichage2DInit();
    void Close();
    ~affichage2D();
};

#endif