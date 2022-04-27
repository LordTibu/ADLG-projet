#include "affichage2D.h"

affichage2D::affichage2D()
{
}

void affichage2D::init2D(){
    SCREEN_WIDTH = 1000;
    SCREEN_HEIGHT = 600;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout <<"Se inicialiso la monda esa \n";
        window = SDL_CreateWindow("test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT,0);
        if(window){
            std::cout << "se creo la ventana al infierno \n";
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            std::cout << "se creo la rendeoroer \n";
        }

        isRun = true;
    }else{
        std::cerr <<" se fue todo a la proronga " << SDL_GetError();
        isRun = false;
    }

    //menu squares
    rectToDraw2 = {SCREEN_WIDTH/2-(SCREEN_HEIGHT/2+SCREEN_HEIGHT/10)/2
                            ,SCREEN_HEIGHT/2,
                            SCREEN_HEIGHT/2+SCREEN_HEIGHT/10
                            , SCREEN_WIDTH/20};

    rectToDraw1= {SCREEN_WIDTH/2-(SCREEN_HEIGHT/2+SCREEN_HEIGHT/10)/2
                            ,SCREEN_HEIGHT/3,
                            SCREEN_HEIGHT/2+SCREEN_HEIGHT/10
                            , SCREEN_WIDTH/20};

    rectToDraw3={SCREEN_WIDTH/2-(SCREEN_HEIGHT/2+SCREEN_HEIGHT/10)/2
                            ,SCREEN_HEIGHT-SCREEN_HEIGHT/3 ,
                            SCREEN_HEIGHT/2+SCREEN_HEIGHT/10 
                            , SCREEN_WIDTH/20};

    rectToDraw4={SCREEN_WIDTH/2-(SCREEN_HEIGHT/2+SCREEN_HEIGHT/10)/2
                            ,SCREEN_HEIGHT-SCREEN_HEIGHT/6,
                            SCREEN_HEIGHT/2+SCREEN_HEIGHT/10
                            , SCREEN_WIDTH/20};
}

void affichage2D::menu2D(){
    SDL_PollEvent (&event);
    
    SDL_SetRenderDrawColor(renderer, 255,0,255,255);
    SDL_RenderClear(renderer);
    //aqui agrego vainas
    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    SDL_RenderFillRect(renderer, &rectToDraw1);
    

    SDL_SetRenderDrawColor(renderer, 0,255,0,255);
    SDL_RenderFillRect(renderer, &rectToDraw2);

    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderFillRect(renderer, &rectToDraw3);

    SDL_SetRenderDrawColor(renderer, 0,255,0,255);
    SDL_RenderFillRect(renderer, &rectToDraw4);

    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_Rect rectToDraw = {event.motion.x,event.motion.y,10,10};
    SDL_RenderFillRect(renderer, &rectToDraw);
    

    SDL_RenderPresent(renderer);

}

void affichage2D::clean2D(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
}

affichage2D::~affichage2D()
{
   
}
