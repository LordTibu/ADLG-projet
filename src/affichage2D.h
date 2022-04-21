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
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    bool isRun;
    affichage2D();
    void init2D();
    void menu2D();
    void clean2D();
    ~affichage2D();
};

#endif