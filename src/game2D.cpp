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
    
    //jeu.gameUpdateNO();
    
    SDL_PollEvent (&aff->event);

    if(!aff->isMenu){
        currentTime = SDL_GetTicks();
        if (currentTime > lastTime + Speed){
            //affichage de cart
                if (cartSelect && aff->event.type == SDL_MOUSEBUTTONDOWN){
                    cartSelect=false;
                }
                for(int i=2;i<jeu.playerDeck.getSize()+2;i++){
                    if (aff->event.type == SDL_MOUSEBUTTONDOWN && float(aff->event.motion.x) >= aff->cartes[i].x && float(aff->event.motion.x) <=(aff->cartes[i].x+aff->cartes[i].w)
                    && float(aff->event.motion.y) >= aff->cartes[i].y && float(aff->event.motion.y)<= (aff->cartes[i].y+aff->cartes[i].h)){
                        cartSelect=true;
                    }
                }

                if(playerTurn){
                    //std::cout << "PLAYER TURN" << std::endl;
                    if(deployPhase){ //DEPLOYMENT PHASE
                    //std::cout <<"deck size = "<< jeu.getplayerdeck().size() << std::endl;
                    //std::cout << "quelle carte voulez vous jouer? - tapez 0 pour abandoner le jeu sinon le # de la carte, 100 pour passer" << std::endl;
                        for(int i=2;i<jeu.playerDeck.getSize()+2;i++){
                            if (aff->event.type == SDL_MOUSEBUTTONDOWN && float(aff->event.motion.x) >= aff->cartes[i].x && float(aff->event.motion.x) <=(aff->cartes[i].x+aff->cartes[i].w)
                            && float(aff->event.motion.y) >= aff->cartes[i].y && float(aff->event.motion.y)<= (aff->cartes[i].y+aff->cartes[i].h)){
                                inputgame=i-1;
                                std::cout<<"you play the card "<< inputgame<<std::endl;
                                if(input > 0 && (unsigned int)inputgame <= jeu.playerDeck.getSize()){
                                    jeu.deployUnitPlayer(inputgame);
                                    deployPhase = !deployPhase;
                                }else {std::cout << "input non reconnu, svp ressayer" << std::endl;}

                            }
                        }
                        if(aff->event.type == SDL_MOUSEBUTTONDOWN && float(aff->event.motion.x) >= aff->cartes[0].x && float(aff->event.motion.x) <=(aff->cartes[0].x+aff->cartes[0].w)
                            && float(aff->event.motion.y) >= aff->cartes[0].y && float(aff->event.motion.y)<= (aff->cartes[0].y+aff->cartes[0].h)){
                            inputgame=100;
                            std::cout<<"PASS "<< inputgame<<std::endl;
                            if(jeu.playerDeck.getSize() > 0){
                                deployPhase = !deployPhase; 
                                }else { 
                                    std::cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << std::endl;
                                    }
                            }

                        if(aff->event.type == SDL_MOUSEBUTTONDOWN && float(aff->event.motion.x) >= aff->cartes[1].x && float(aff->event.motion.x) <=(aff->cartes[1].x+aff->cartes[1].w)
                            && float(aff->event.motion.y) >= aff->cartes[1].y && float(aff->event.motion.y)<= (aff->cartes[1].y+aff->cartes[1].h)){
                            inputgame=0;
                            std::cout<<"QUIT "<< inputgame<<std::endl;
                            }
                    }else{//PHASE DE BATAILLE
                        if(aff->event.type == SDL_MOUSEBUTTONDOWN && float(aff->event.motion.x) >= aff->cartes[1].x && float(aff->event.motion.x) <=(aff->cartes[1].x+aff->cartes[1].w)
                                && float(aff->event.motion.y) >= aff->cartes[1].y && float(aff->event.motion.y)<= (aff->cartes[1].y+aff->cartes[1].h)){
                                inputgame=0;
                                std::cout<<"QUIT "<< inputgame<<std::endl;
                                }
                        //esta boucle lee las casillas 
                        for(int ii = 0; ii < tailleG; ++ii) {
                            for(int jj = 0; jj < tailleG; ++jj) {
                                if (aff->event.type == SDL_MOUSEBUTTONDOWN && float(aff->event.motion.x) >= aff->table[ii][jj].x && float(aff->event.motion.x) <=(aff->table[ii][jj].x+aff->table[ii][jj].w)
                                    && float(aff->event.motion.y) >= aff->table[ii][jj].y && float(aff->event.motion.y)<= (aff->table[ii][jj].y+aff->table[ii][jj].h)){
                                        
                                        std::cout<< "x = "<<ii<<"  y = "<<jj<<std::endl;

                                        }
                                    }
                                }       
                    }
                    
                }
                
                lastTime = currentTime; //necessary
                //std::cout<< aff->event.motion.x << " , "<<aff->event.motion.y<<std::endl;
            }
    } 
        
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
            currentTime = SDL_GetTicks();
			if (currentTime > lastTime + Speed)
			{
                    if (float(aff->event.motion.x) >= aff->rectToDraw1.x && float(aff->event.motion.x) <=(aff->rectToDraw1.x+aff->rectToDraw1.w)
                && float(aff->event.motion.y) >= aff->rectToDraw1.y && float(aff->event.motion.y)<= (aff->rectToDraw1.y+aff->rectToDraw1.h)){
                    std::cout << "rect 1 \n";
                    jeu.gameInit(tailleG, tailleG);
                    std::cout<< jeu.playerDeck.getSize()  << " esto era una el tamano"<<std::endl;
                    aff->initdeck2D(jeu.playerDeck.getSize() ,tailleG);
                    input=1;
                    aff->erasemenu2D();
                    isNOInit = false;
                    }  
                    if (float(aff->event.motion.x) >= aff->rectToDraw2.x && float(aff->event.motion.x) <=(aff->rectToDraw2.x+aff->rectToDraw2.w)
                && float(aff->event.motion.y) >= aff->rectToDraw2.y && float(aff->event.motion.y)<= (aff->rectToDraw2.y+aff->rectToDraw2.h)){
                    std::cout << "rect 2 \n";
                    jeu.gameInitServer(tailleG, tailleG);
                    aff->initdeck2D(jeu.playerDeck.getSize() ,tailleG);
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
                    aff->initdeck2D(jeu.playerDeck.getSize() ,tailleG);
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
                    lastTime = currentTime; //necessary
                }               
            }
            break;
        default:
            break;
     
    }   
}

void game2D::updategame2D(){
    while(aff->isRun){
        menu2D();
        aff->menu2D();
        aff->drawGame(tailleG,jeu.playerDeck.getSize(),cartSelect,playerTurn);
        if(!isNOInit)typegame();
    }
}

void game2D::cleangame2D(){
    aff->clean2D(jeu.playerDeck.getSize() );
    
    delete aff;
    aff = NULL;
}

game2D::~game2D(){

}



