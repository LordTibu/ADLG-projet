#include "game2D.h"

game2D::game2D(){

}

void game2D::initgame2D(){
    aff=new affichage2D();
    aff->init2D();
    input = NULL;
    isNOInit= true;
    tailleG=5;
}

void game2D::local(){
    
    jeu.gameUpdateNO();
        
}

void game2D::mulplayerserver(){
     
    jeu.gameUpdateNETNO();
}

void game2D::connectmultiplayer(){

    jeu.gameUpdateNETClientNO();
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
            if(input == NULL && aff->isMenu){
                    if (float(aff->event.motion.x) >= aff->rectToDraw1.x && float(aff->event.motion.x) <=(aff->rectToDraw1.x+aff->rectToDraw1.w)
                && float(aff->event.motion.y) >= aff->rectToDraw1.y && float(aff->event.motion.y)<= (aff->rectToDraw1.y+aff->rectToDraw1.h)){
                    std::cout << "rect 1 \n";
                    jeu.gameInit(tailleG, tailleG);
                    aff->initdeck2D(jeu.getplayerdeck().size(),tailleG);
                    input=1;
                    aff->erasemenu2D();
                    isNOInit = false;
                    }  
                    if (float(aff->event.motion.x) >= aff->rectToDraw2.x && float(aff->event.motion.x) <=(aff->rectToDraw2.x+aff->rectToDraw2.w)
                && float(aff->event.motion.y) >= aff->rectToDraw2.y && float(aff->event.motion.y)<= (aff->rectToDraw2.y+aff->rectToDraw2.h)){
                    std::cout << "rect 2 \n";
                    jeu.gameInitServer(tailleG, tailleG);
                    aff->initdeck2D(jeu.getplayerdeck().size(),tailleG);
                    input=2;
                    aff->erasemenu2D();
                    isNOInit = false;
                    } 
                    if (float(aff->event.motion.x) >= aff->rectToDraw3.x && float(aff->event.motion.x) <=(aff->rectToDraw3.x+aff->rectToDraw3.w)
                && float(aff->event.motion.y) >= aff->rectToDraw3.y&& float(aff->event.motion.y)<= (aff->rectToDraw3.y +aff->rectToDraw3.h)){
                    std::cout << "rect 3 \n";
                    std::string argv1;
                    std::cout << "saisir l'ip du server :";
                    std::cin>>argv1;

                    jeu.gameInitClient(tailleG,tailleG,(char*)argv1.c_str(),5000);
                    aff->initdeck2D(jeu.getplayerdeck().size(),tailleG);
                    input=3;
                    aff->erasemenu2D();
                    isNOInit = false;
                    } 
                    if (float(aff->event.motion.x) >= aff->rectToDraw4.x && float(aff->event.motion.x) <=(aff->rectToDraw4.x+aff->rectToDraw4.w)
                && float(aff->event.motion.y) >= aff->rectToDraw4.y && float(aff->event.motion.y)<= (aff->rectToDraw4.y+aff->rectToDraw4.h)){
                    std::cout << "rect 4 \n";
                    std::cout<<"deck builder";
                    input=4;
                    aff->erasemenu2D();
                    isNOInit = false;
                    }  
                    std::cout << " ya se acabo\n";
            }
            
            if(input !=NULL && !aff->isMenu){
                for(int i=0;i<jeu.getplayerdeck().size();i++){
                    if (float(aff->event.motion.x) >= aff->cartes[i].x && float(aff->event.motion.x) <=(aff->cartes[i].x+aff->cartes[i].w)
                && float(aff->event.motion.y) >= aff->cartes[i].y && float(aff->event.motion.y)<= (aff->cartes[i].y+aff->cartes[i].h)){
                    std::cout<<"oprime en carta" << i;
                    cartSelect=true;
                    }
                }
            }
                std::cout<< aff->event.motion.x << " , "<<aff->event.motion.y<<std::endl;
                break;
        default:
            break;
     
    }   
}

void game2D::updategame2D(){
    while(aff->isRun){
        menu2D();
        aff->menu2D();
        std::cout << int(cartSelect)<<std::endl;
        aff->drawGame(tailleG,jeu.getplayerdeck().size(),cartSelect);
        //if(!isNOInit)typegame();
    }
}

void game2D::cleangame2D(){
    aff->clean2D(jeu.getplayerdeck().size());
    
    delete aff;
    aff = NULL;
}

game2D::~game2D(){

}



