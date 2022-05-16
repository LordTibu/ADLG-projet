#include "affichage2D.h"

affichage2D::affichage2D()
{
}

void affichage2D::init2D(){
    SCREEN_WIDTH = 1440;
    SCREEN_HEIGHT = 900;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout <<"Se inicialiso la monda esa \n";
        window = SDL_CreateWindow("ADLG",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,0);
        if(window){
            std::cout << "se creo la ventana al infierno \n";
        }else{std::cout << "se cago todo"<<std::endl;}
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


    rectPlayer = {0,SCREEN_HEIGHT-SCREEN_HEIGHT/5,
                    SCREEN_WIDTH/10,SCREEN_HEIGHT/5};

    SDL_Surface * surface=IMG_Load("assets/menu/start1.png");
    Menu1 = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("assets/menu/start2.png");
    Menu2 = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("assets/menu/start3.png");
    Menu3 = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("assets/menu/start4.png");
    Menu4 = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("assets/menu/back.png");
    backmenu = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("assets/game/back.png");
    backgame = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("assets/game/backcard.png");
    backcard = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("assets/game/cardslct.png");
    cardselect = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    
    surface=IMG_Load("assets/game/jesucristo.png");
    jesucristo = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("assets/game/soldat.png");
    soldat = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("assets/game/archer.png");
    archer = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("assets/game/peasant.png");
    peasant = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("assets/game/shinobi.png");
    shinobi = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("assets/game/samurai.png");
    samurai = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load("assets/game/case.png");
    square = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
}

void affichage2D::initdeck2D(int n, int d){

    cartes = new SDL_Rect [n+2];

    cartes[0]= {rectPlayer.w +(SCREEN_WIDTH/40),SCREEN_HEIGHT-SCREEN_HEIGHT/10,
            SCREEN_WIDTH/20,SCREEN_HEIGHT/6};
    
    for(int i=1;i<n+2;i++){
        cartes[i]= {(cartes[i-1].x+3*(SCREEN_WIDTH/40)) ,SCREEN_HEIGHT-SCREEN_HEIGHT/10,
            SCREEN_WIDTH/20,SCREEN_HEIGHT/6};   
    }

    table = new SDL_Rect* [d];

    for(int z = 0; z < d; ++z) {
        table[z] = new SDL_Rect[d];
    }

    for(int i = 0; i < d; ++i) {
        for(int j = 0; j < d; ++j) {
            table[i][j]= {int(SCREEN_WIDTH/8+0.1*SCREEN_WIDTH + j*(SCREEN_WIDTH/6+n*0.1*SCREEN_WIDTH)/5), 
            int(SCREEN_HEIGHT/20+0.1*SCREEN_HEIGHT + i*(SCREEN_HEIGHT/24+0.1*SCREEN_HEIGHT)),
        int((SCREEN_WIDTH/10+n*0.1*SCREEN_WIDTH)/5), int(SCREEN_HEIGHT/20+n*0.1*SCREEN_HEIGHT)/n};

        }
    }

    PlayerUnits= new SDL_Rect[n];
    EnnemyUnits = new SDL_Rect[n];
}

void affichage2D::erasemenu2D(){
    isMenu = false;
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void affichage2D::menu2D(){
    SDL_PollEvent (&event);
    if(isMenu){
    
    SDL_RenderCopy(renderer, backmenu, NULL, NULL);

    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    SDL_RenderCopy(renderer, Menu1, NULL, &rectToDraw1);
    

    SDL_SetRenderDrawColor(renderer, 0,255,0,255);
    SDL_RenderCopy(renderer, Menu2, NULL, &rectToDraw2);
    

    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderCopy(renderer, Menu3, NULL, &rectToDraw3);
    

    SDL_SetRenderDrawColor(renderer, 0,255,0,255);
    SDL_RenderCopy(renderer, Menu4, NULL, &rectToDraw4);

    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_Rect rectToDraw = {event.motion.x,event.motion.y,10,10};
    SDL_RenderFillRect(renderer, &rectToDraw);
    SDL_RenderPresent(renderer);
    }

}

void affichage2D::drawUnit(int posx,int posy){
    SDL_Rect pos= {table[posx][posy].x+20,table[posx][posy].y+20,20,20};
    SDL_RenderFillRect(renderer, &pos);
}

void affichage2D::drawallunits(std::vector<unit> Units,bool player){
    for(auto i = Units.begin(); i != Units.end(); i++){
        if((*i).getName()=="jeP") SDL_SetRenderDrawColor(renderer, 255,255,229,255);
        else if(player){
            SDL_SetRenderDrawColor(renderer, 153,0,0,255);
        }

        if((*i).getName()=="jeE") SDL_SetRenderDrawColor(renderer, 255,255,51,255);
        else if (!player){
            SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        }
        drawUnit((*i).getX(),(*i).getY());
    }
}

void affichage2D::drawTable(int n){
    SDL_RenderCopy(renderer,backgame,NULL,NULL);

    for(int x=0; x<n;x++){
        for(int y=0;y<n;y++){
            SDL_RenderCopy(renderer,square,NULL,&table[x][y]);
            /*SDL_SetRenderDrawColor(renderer, 0,255,0,255);
            SDL_RenderFillRect(renderer, &table[x][y]);*/
        }
    }
}

void affichage2D::drawDeck(int n, bool player){
    if(player){
    SDL_SetRenderDrawColor(renderer, 153,0,0,255);
    }else{SDL_SetRenderDrawColor(renderer, 0,0,0,255);}
    SDL_RenderFillRect(renderer, &rectPlayer);

    //PASS
    SDL_SetRenderDrawColor(renderer, 32,32,32,255);
    SDL_RenderFillRect(renderer, &cartes[0]);
    //QUIT
    SDL_SetRenderDrawColor(renderer, 160,160,160,255);
    SDL_RenderFillRect(renderer, &cartes[1]);

    for(int i=2;i<n+2;i++){
        if(i==idCard)SDL_RenderCopy(renderer, cardselect, NULL, &cartes[i]);
        else SDL_RenderCopy(renderer, backcard, NULL, &cartes[i]);   
    }

}

void affichage2D::drawCart(bool cart){
    SDL_Rect pos= {0,SCREEN_HEIGHT/2-150,200,300};
    if(cart){
        if(nameCard=="archer" || nameCard=="arP" || nameCard=="arE")SDL_RenderCopy(renderer,archer,NULL,&pos);
        if(nameCard=="shinobi"|| nameCard=="shP" || nameCard=="shE")SDL_RenderCopy(renderer,shinobi,NULL,&pos);
        if(nameCard=="samurai"|| nameCard=="saP" || nameCard=="saE")SDL_RenderCopy(renderer,samurai,NULL,&pos);
        if(nameCard=="jesucristo"|| nameCard=="jeP" || nameCard=="jeE")SDL_RenderCopy(renderer,jesucristo,NULL,&pos);
        if(nameCard=="peasant"|| nameCard=="peP" || nameCard=="peE")SDL_RenderCopy(renderer,peasant,NULL,&pos);
        if(nameCard=="soldat"|| nameCard=="soP" || nameCard=="soE")SDL_RenderCopy(renderer,soldat,NULL,&pos);
    }else{
        SDL_RenderCopy(renderer, backcard,NULL,&pos);
    }  

 
}

void affichage2D::drawGame(int n, int d, bool cart,bool player,std::vector<unit> UnitsPlayer, std::vector<unit> UnitsEnnemy){
    if(!isMenu){
        drawTable(n);
        drawDeck(d,player);
        drawCart(cart);
        drawallunits(UnitsPlayer,true);
        
        drawallunits(UnitsEnnemy,false);


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
    delete [] PlayerUnits;
    delete [] EnnemyUnits;
    SDL_Quit();
}

affichage2D::~affichage2D()
{
   
}
