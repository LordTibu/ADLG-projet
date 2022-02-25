#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

/*! \class game
    \brief class qui gère le game

    Cette classe me chuâ los gvos
*/
class game
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event events;
    bool stay = true;
public:
    game();
    ~game();
    void game_init();
    void game_handleEvents();
    void game_update();
    void game_render();
    void game_exit();
};


