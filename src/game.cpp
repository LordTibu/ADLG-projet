#include "game.h"

game::game() {
    window = NULL;
    renderer = NULL;
}

game::~game() {}

void game::game_init() {
    SDL_Init(SDL_INIT_VIDEO);
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur dans l'init de SDL2_Video: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    window = SDL_CreateWindow("Videojuego", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, 0);
    if(window == NULL){
        std::cout << "Erreur dans l'init de la fenetre: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        std::cout << "Erreur dans l'init du renderer: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    
}   

void game::game_handleEvents() {
    // tant qu'il y a des evenements � traiter (cette boucle n'est pas bloquante)
    while (SDL_PollEvent(&events)) {
        if (events.type == SDL_QUIT) stay = false;           // Si l'utilisateur a clique sur la croix de fermeture
        else if (events.type == SDL_KEYDOWN) {              // Si une touche est enfoncee
            switch (events.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:                       // Si la touche "Esc" est enfoncee arret du programme
                stay = false;
                break;
            case SDL_SCANCODE_T:                            // Si la touche T est enfoncee l'image fait zoom
                break;
            case SDL_SCANCODE_G:                            // Si la touche G est enfoncee l'image fait dezoom
                break;
            default: break;
            }
        }
    }
}

void game::game_update() {
    
}

void game::game_render() {

}

void game::game_exit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
