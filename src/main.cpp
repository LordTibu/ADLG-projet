#include "game.h"

int main(void) {
    game ElNegroGoloso;
    const float FPS = 60;
    float const frames = 1000.f / FPS;
    Uint32 frameStart;
    int frametime;
    bool stay = true;
    ElNegroGoloso.game_init();

    while(stay){

        frameStart = SDL_GetTicks();
        
        ElNegroGoloso.game_update();
        ElNegroGoloso.game_render();

        frametime = SDL_GetTicks() - frameStart;
        if(frames > frametime){
            SDL_Delay(frames - frametime);
        }

    }
    ElNegroGoloso.game_exit();
    
    return 0;
}