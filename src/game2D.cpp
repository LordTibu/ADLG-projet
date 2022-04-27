#include "game2D.h"

game2D::game2D(){

}

void game2D::initgame2D(){
    aff=new affichage2D();
    aff->init2D();
    input = NULL;
}

void game2D::local(){
    jeu.gameInit(5, 5);
        while(jeu.Stay()){
            jeu.gameUpdate();
        }
}

void game2D::mulplayerserver(){
    jeu.gameInitServer(5, 5);
    jeu.gameUpdateNET();
}

void game2D::connectmultiplayer(){
    std::string argv1;
    std::cout << "saisir l'ip du server :";
    std::cin>>argv1;

    jeu.gameInitClient(5,5,(char*)argv1.c_str(),5000);
    jeu.gameUpdateNETClient();
}

void game2D::typegame(){
    if(input == 1){
        local();
    }

    if(input ==2){
        mulplayerserver();
    }

    if(input==3){
        connectmultiplayer();
    }

    if(input==4){
        //aqui va el deck builder
        std::cout<<"deck builder";
    }
    
}

void game2D::menu2D(){
    SDL_PollEvent (&aff->event);

    switch (aff->event.type){
        case SDL_QUIT:
            aff->isRun = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
        if(input == NULL){
                if (float(aff->event.motion.x) >= aff->rectToDraw1.x && float(aff->event.motion.x) <=(aff->rectToDraw1.x+aff->rectToDraw1.w)
            && float(aff->event.motion.y) >= aff->rectToDraw1.y && float(aff->event.motion.y)<= (aff->rectToDraw1.y+aff->rectToDraw1.h)){
                std::cout << "rect 1 \n";
                input=1;
                }  
                if (float(aff->event.motion.x) >= aff->rectToDraw2.x && float(aff->event.motion.x) <=(aff->rectToDraw2.x+aff->rectToDraw2.w)
            && float(aff->event.motion.y) >= aff->rectToDraw2.y && float(aff->event.motion.y)<= (aff->rectToDraw2.y+aff->rectToDraw2.h)){
                std::cout << "rect 2 \n";
                input=2;
                } 
                if (float(aff->event.motion.x) >= aff->rectToDraw3.x && float(aff->event.motion.x) <=(aff->rectToDraw3.x+aff->rectToDraw3.w)
            && float(aff->event.motion.y) >= aff->rectToDraw3.y&& float(aff->event.motion.y)<= (aff->rectToDraw3.y +aff->rectToDraw3.h)){
                std::cout << "rect 3 \n";
                input=3;
                } 
                if (float(aff->event.motion.x) >= aff->rectToDraw4.x && float(aff->event.motion.x) <=(aff->rectToDraw4.x+aff->rectToDraw4.w)
            && float(aff->event.motion.y) >= aff->rectToDraw4.y && float(aff->event.motion.y)<= (aff->rectToDraw4.y+aff->rectToDraw4.h)){
                std::cout << "rect 4 \n";
                input=4;
                }  
                std::cout << " ya se acabo\n";
        }
            //std::cout<< event.motion.x << " , "<<event.motion.y<<std::endl;
            break;
        default:
            break;

    }
}

void game2D::updategame2D(){
    while(aff->isRun){
        menu2D();
        typegame();
        aff->menu2D();
    }
}

void game2D::cleangame2D(){
    aff->clean2D();
    
    delete aff;
    aff = NULL;
}

game2D::~game2D(){

}



