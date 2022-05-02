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

    isMenu = true;

    rectPlayer = {0,SCREEN_HEIGHT-SCREEN_HEIGHT/5,
                    SCREEN_WIDTH/10,SCREEN_HEIGHT/5};
    
}

void affichage2D::initdeck2D(int n, int d){

    cartes = new SDL_Rect [5];

    cartes[0]= {rectPlayer.w +(SCREEN_WIDTH/40),SCREEN_HEIGHT-SCREEN_HEIGHT/10,
            SCREEN_WIDTH/20,SCREEN_HEIGHT/6};
    
    for(int i=1;i<n;i++){
        cartes[i]= {(cartes[i-1].x+3*(SCREEN_WIDTH/40)) ,SCREEN_HEIGHT-SCREEN_HEIGHT/10,
            SCREEN_WIDTH/20,SCREEN_HEIGHT/6};   
    }

    table = new SDL_Rect* [d];

    for(int z = 0; z < d; ++z) {
        table[z] = new SDL_Rect[d];
    }

    for(int i = 0; i < d; ++i) {
        for(int j = 0; j < d; ++j) {
            table[i][j]= {int(SCREEN_WIDTH/8+0.1*SCREEN_WIDTH + i*(SCREEN_WIDTH/6+n*0.1*SCREEN_WIDTH)/5), 
            int(SCREEN_HEIGHT/20+0.1*SCREEN_HEIGHT + j*(SCREEN_HEIGHT/24+0.1*SCREEN_HEIGHT)),
        int((SCREEN_WIDTH/10+n*0.1*SCREEN_WIDTH)/5), int(SCREEN_HEIGHT/20+n*0.1*SCREEN_HEIGHT)/n};

        }
    }
}

void affichage2D::erasemenu2D(){
    isMenu = false;
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void affichage2D::menu2D(){
    SDL_PollEvent (&event);
    if(isMenu){
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

}

void affichage2D::drawTable(int n){

    SDL_SetRenderDrawColor(renderer, 0,0,200,200);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0,255,0,255);

    /*for(int i=1; i<=n;i++){
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH/6+0.1*SCREEN_WIDTH, SCREEN_HEIGHT/6+i*0.1*SCREEN_HEIGHT,
        SCREEN_WIDTH/6+n*0.1*SCREEN_WIDTH, SCREEN_HEIGHT/6+i*0.1*SCREEN_HEIGHT);
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH/6+i*0.1*SCREEN_WIDTH, SCREEN_HEIGHT/6+0.1*SCREEN_HEIGHT,
        SCREEN_WIDTH/6+i*0.1*SCREEN_WIDTH, SCREEN_HEIGHT/6+n*0.1*SCREEN_HEIGHT);
    } */

    bool pedo = true;
    for(int x=0; x<n;x++){
        for(int y=0;y<n;y++){
            if(pedo){SDL_SetRenderDrawColor(renderer, 255,255,255,255);}
            else { SDL_SetRenderDrawColor(renderer, 255,255,0,255);}

            SDL_RenderFillRect(renderer, &table[x][y]);
            pedo = !pedo;
        }
    }
}

void affichage2D::drawDeck(int n){
    SDL_SetRenderDrawColor(renderer, 255,0,255,255);
    SDL_RenderFillRect(renderer, &rectPlayer);
    
    SDL_SetRenderDrawColor(renderer, 255,0,0,0);
    for(int i=0;i<n;i++){
      SDL_RenderFillRect(renderer, &cartes[i]);        
    }
    
}

void affichage2D::drawGame(int n, int d){
    if(!isMenu){
        drawTable(n);
        drawDeck(d);


        
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_Rect rectToDraw = {event.motion.x,event.motion.y,10,10};
        SDL_RenderFillRect(renderer, &rectToDraw);
        SDL_RenderPresent(renderer);
    }
}

void affichage2D::clean2D(int n){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    for(int i = 0; i < n; ++i) {
        delete table[i];
    }
    delete [] cartes;
    delete [] table;
    SDL_Quit();
}

affichage2D::~affichage2D()
{
   
}
