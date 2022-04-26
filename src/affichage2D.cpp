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
}

void affichage2D::menu2D(){
    SDL_Event event;
    SDL_Rect rectToDraw2 = {SCREEN_WIDTH/2-(SCREEN_HEIGHT/2+SCREEN_HEIGHT/10)/2
                            ,SCREEN_HEIGHT/2,
                            SCREEN_HEIGHT/2+SCREEN_HEIGHT/10
                            , SCREEN_WIDTH/20};

    SDL_Rect rectToDraw1= {SCREEN_WIDTH/2-(SCREEN_HEIGHT/2+SCREEN_HEIGHT/10)/2
                            ,SCREEN_HEIGHT/3,
                            SCREEN_HEIGHT/2+SCREEN_HEIGHT/10
                            , SCREEN_WIDTH/20};

    SDL_Rect rectToDraw3={SCREEN_WIDTH/2-(SCREEN_HEIGHT/2+SCREEN_HEIGHT/10)/2
                            ,SCREEN_HEIGHT-SCREEN_HEIGHT/3 ,
                            SCREEN_HEIGHT/2+SCREEN_HEIGHT/10 
                            , SCREEN_WIDTH/20};

    SDL_Rect rectToDraw4={SCREEN_WIDTH/2-(SCREEN_HEIGHT/2+SCREEN_HEIGHT/10)/2
                            ,SCREEN_HEIGHT-SCREEN_HEIGHT/6,
                            SCREEN_HEIGHT/2+SCREEN_HEIGHT/10
                            , SCREEN_WIDTH/20};
    SDL_PollEvent (&event);
    switch (event.type){
        case SDL_QUIT:
            isRun = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (float(event.motion.x) >= rectToDraw1.x && float(event.motion.x) <=(rectToDraw1.x+rectToDraw1.w)
        && float(event.motion.y) >= rectToDraw1.y && float(event.motion.y)<= (rectToDraw1.y+rectToDraw1.h)){
            std::cout << "rect 1 \n";
            }  
            if (float(event.motion.x) >= rectToDraw2.x && float(event.motion.x) <=(rectToDraw2.x+rectToDraw2.w)
        && float(event.motion.y) >= rectToDraw2.y && float(event.motion.y)<= (rectToDraw2.y+rectToDraw2.h)){
            std::cout << "rect 2 \n";
            } 
            if (float(event.motion.x) >= rectToDraw3.x && float(event.motion.x) <=(rectToDraw3.x+rectToDraw3.w)
        && float(event.motion.y) >= rectToDraw3.y&& float(event.motion.y)<= (rectToDraw3.y +rectToDraw3.h)){
            std::cout << "rect 3 \n";
            } 
            if (float(event.motion.x) >= rectToDraw4.x && float(event.motion.x) <=(rectToDraw4.x+rectToDraw4.w)
        && float(event.motion.y) >= rectToDraw4.y && float(event.motion.y)<= (rectToDraw4.y+rectToDraw4.h)){
            std::cout << "rect 4 \n";
            }  
            std::cout << " ya se acabo\n";
            
            //std::cout<< event.motion.x << " , "<<event.motion.y<<std::endl;
            break;
        default:
            break;

    }
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
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

affichage2D::~affichage2D()
{
   
}
