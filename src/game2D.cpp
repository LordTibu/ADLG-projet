#include "game2D.h"

game2D::game2D(){

}

void game2D::initgame2D(){
    aff=new affichage2D();
    aff->init2D();
    input = -1;
    isNOInit= true;
    tailleG=5;
}

void game2D::local(){    
    SDL_PollEvent (&aff->event);
    if(!aff->isMenu){
        
            
            if(jeu.playerTurn){
                if(jeu.deployPhase){//PHASE DEPLOY
                    isUnits = false;
                    //affichage de cart
                    if (aff->event.type == SDL_MOUSEBUTTONDOWN && (float(aff->event.motion.x) < aff->table[0][0].x || float(aff->event.motion.x) > (aff->table[tailleG-1][tailleG-1].x))
                        && (float(aff->event.motion.y) < aff->table[0][0].y || float(aff->event.motion.y) > (aff->table[tailleG-1][tailleG-1].y))){
                        cartSelect=false;
                        aff->idCard=0;
                    }


                    //GESTION DEFAULT 
                    if(aff->event.type == SDL_MOUSEBUTTONDOWN){
                        for(int i=2;i<jeu.playerDeck.getSize()+2;i++){
                            if (float(aff->event.motion.x) >= aff->cartes[i].x && float(aff->event.motion.x) <=(aff->cartes[i].x+aff->cartes[i].w)
                            && float(aff->event.motion.y) >= aff->cartes[i].y && float(aff->event.motion.y)<= (aff->cartes[i].y+aff->cartes[i].h)){
                                if(aff->event.button.button == SDL_BUTTON_RIGHT){
                                    cartSelect=true;
                                    inputgame=i-1;
                                    std::cout<<"you selected the card "<< inputgame<<std::endl;
                                    aff->idCard=i;
                                    aff->nameCard=jeu.playerDeck[inputgame-1].getName();
                                }
                                if(aff->event.button.button == SDL_BUTTON_LEFT && inputgame > 0 && inputgame <= jeu.playerDeck.getSize()){
                                    jeu.deployUnitPlayer(inputgame);
                                    std::cout << "deploy card #"<<inputgame<<std::endl;
                                }else if(aff->event.button.button == SDL_BUTTON_LEFT){
                                    std::cout << "input non reconnu, svp ressayer" << std::endl;
                                }
                            }
                        }
                    }

                    //GESTION DU QUIT
                    if(aff->event.type == SDL_MOUSEBUTTONDOWN && float(aff->event.motion.x) >= aff->cartes[1].x && float(aff->event.motion.x) <=(aff->cartes[1].x+aff->cartes[1].w)
                    && float(aff->event.motion.y) >= aff->cartes[1].y && float(aff->event.motion.y)<= (aff->cartes[1].y+aff->cartes[1].h)){
                        inputgame=0;
                        std::cout<<"QUIT "<< inputgame<<std::endl;
                        aff->isRun=false;
                    }

                    //GESTION DU PASS
                    if(aff->event.type == SDL_MOUSEBUTTONDOWN && float(aff->event.motion.x) >= aff->cartes[0].x && float(aff->event.motion.x) <=(aff->cartes[0].x+aff->cartes[0].w)
                        && float(aff->event.motion.y) >= aff->cartes[0].y && float(aff->event.motion.y)<= (aff->cartes[0].y+aff->cartes[0].h)){
                        inputgame=100;
                        std::cout<<"PASS "<< inputgame<<std::endl;
                        std::cout<<jeu.playerUnits.size()<<std::endl;
                        if(jeu.playerUnits.size() > 0){
                            jeu.deployPhase = !jeu.deployPhase; 
                        }
                        else { 
                            std::cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << std::endl;
                            }
                    }
                }
                else{//PHASE DE BATAILLE
                    isUnits=true;

                    //affichage du cart
                    if(aff->event.type == SDL_MOUSEBUTTONDOWN){
                        for(int i=2;i<int(jeu.playerUnits.size())+2;i++){
                            if (float(aff->event.motion.x) >= aff->cartes[i].x && float(aff->event.motion.x) <=(aff->cartes[i].x+aff->cartes[i].w)
                            && float(aff->event.motion.y) >= aff->cartes[i].y && float(aff->event.motion.y)<= (aff->cartes[i].y+aff->cartes[i].h)){
                                if(aff->event.button.button == SDL_BUTTON_RIGHT){
                                    cartSelect=true;
                                    inputgame=i-1;
                                    std::cout<<"you selected the unit "<< inputgame<<std::endl;
                                    aff->nameCard=jeu.playerUnits[inputgame-1].getName();
                                    aff->idCard=i;
                                }
                            }
                        }
                    }
                    
                    if(cartSelect && aff->event.type == SDL_MOUSEBUTTONDOWN){
                        for(int ii = 0; ii < tailleG; ++ii) {
                            for(int jj = 0; jj < tailleG; ++jj) {
                                if (float(aff->event.motion.x) >= aff->table[ii][jj].x && float(aff->event.motion.x) <=(aff->table[ii][jj].x+aff->table[ii][jj].w)
                                && float(aff->event.motion.y) >= aff->table[ii][jj].y && float(aff->event.motion.y)<= (aff->table[ii][jj].y+aff->table[ii][jj].h)){ 
                                    std::cout<< "x = "<<ii<<"  y = "<<jj<<std::endl;
                                    if(inputgame > 0 && (unsigned int)inputgame <= jeu.playerUnits.size()){
                                        if(jeu.actUnit){
                                            std::cout << "a quelle case bouger l'unite?" << std::endl;
                                            std::cout <<"inputgame = "<<inputgame<<std::endl;
                                            jeu.xmove=ii;
                                            jeu.ymove=jj;
                                            std::cout<< "xmove = "<<jeu.xmove<<"  ymove = "<<jeu.ymove<<std::endl;
                                            if(0 <= jeu.xmove && jeu.xmove < jeu.dim && 0 <= jeu.ymove && jeu.ymove < jeu.dim){
                                                if(!jeu.GB.getTable()[jeu.ymove*jeu.dim+jeu.xmove].isOccupied()){ //Si non occupé, on bouge
                                                   jeu.moveUnitPlayer(inputgame);
                                                    aff->posx = ii;
                                                    aff->posy = jj;
                                                    aff->cardDisplayed = true;
                                                }
                                                else {
                                                    jeu.attackByPlayer(inputgame);
                                                }
                                            }
                                            else {std::cout << "position non valide dans le tableau, svp reesayer" << std::endl;}
                                        } 
                                    }
                                    else {std::cout << "input non reconnu, svp ressayer" << std::endl;}
                                    jeu.actUnit = true;
                                }
                            }
                        } 
                    }

                    //GESTION DU QUIT
                    if(aff->event.type == SDL_MOUSEBUTTONDOWN && float(aff->event.motion.x) >= aff->cartes[1].x && float(aff->event.motion.x) <=(aff->cartes[1].x+aff->cartes[1].w)
                    && float(aff->event.motion.y) >= aff->cartes[1].y && float(aff->event.motion.y)<= (aff->cartes[1].y+aff->cartes[1].h)){
                        inputgame=0;
                        std::cout<<"QUIT "<< inputgame<<std::endl;
                        aff->isRun=false;
                    }
                }
            }
            else {//ENNEMY TURN
                if(jeu.deployPhase){
                    isUnits = false;
                    //affichage de cart
                    if (aff->event.type == SDL_MOUSEBUTTONDOWN && (float(aff->event.motion.x) < aff->table[0][0].x || float(aff->event.motion.x) > (aff->table[tailleG-1][tailleG-1].x))
                        && (float(aff->event.motion.y) < aff->table[0][0].y || float(aff->event.motion.y) > (aff->table[tailleG-1][tailleG-1].y))){
                        cartSelect=false;
                        aff->idCard=0;
                    }


                    //GESTION DEFAULT 
                    if(aff->event.type == SDL_MOUSEBUTTONDOWN){
                        for(int i=2;i<jeu.ennemyDeck.getSize()+2;i++){
                            if (float(aff->event.motion.x) >= aff->cartes[i].x && float(aff->event.motion.x) <=(aff->cartes[i].x+aff->cartes[i].w)
                            && float(aff->event.motion.y) >= aff->cartes[i].y && float(aff->event.motion.y)<= (aff->cartes[i].y+aff->cartes[i].h)){
                                if(aff->event.button.button == SDL_BUTTON_RIGHT){
                                    cartSelect=true;
                                    inputgame=i-1;
                                    std::cout<<"you selected the card "<< inputgame<<std::endl;
                                    aff->idCard=i;
                                    aff->nameCard=jeu.ennemyDeck[inputgame-1].getName();
                                }

                                if(aff->event.button.button == SDL_BUTTON_LEFT && inputgame > 0 && inputgame <= jeu.ennemyDeck.getSize()){
                                    if(!jeu.GB.getTable()[4 * jeu.dim + 4].isOccupied()){
                                        jeu.deployUnitEnnemy(inputgame);
                                        std::cout << "deploy card #"<<inputgame<<std::endl;
                                    } else std::cout << "La base est deja occupée, deployer une unite est impossible" << std::endl;
                                }else if(aff->event.button.button == SDL_BUTTON_LEFT){
                                    std::cout << "input non reconnu, svp ressayer" << std::endl;
                                }
                            }
                        }
                    }

                    //GESTION DU QUIT
                    if(aff->event.type == SDL_MOUSEBUTTONDOWN && float(aff->event.motion.x) >= aff->cartes[1].x && float(aff->event.motion.x) <=(aff->cartes[1].x+aff->cartes[1].w)
                    && float(aff->event.motion.y) >= aff->cartes[1].y && float(aff->event.motion.y)<= (aff->cartes[1].y+aff->cartes[1].h)){
                        inputgame=0;
                        std::cout<<"QUIT "<< inputgame<<std::endl;
                        aff->isRun=false;
                    }

                    //GESTION DU PASS
                    if(aff->event.type == SDL_MOUSEBUTTONDOWN && float(aff->event.motion.x) >= aff->cartes[0].x && float(aff->event.motion.x) <=(aff->cartes[0].x+aff->cartes[0].w)
                        && float(aff->event.motion.y) >= aff->cartes[0].y && float(aff->event.motion.y)<= (aff->cartes[0].y+aff->cartes[0].h)){
                        inputgame=100;
                        std::cout<<"PASS "<< inputgame<<std::endl;
                        std::cout<<jeu.ennemyUnits.size()<<std::endl;
                        if(jeu.ennemyUnits.size() > 0){
                            jeu.deployPhase = !jeu.deployPhase; 
                        }
                        else { 
                            std::cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << std::endl;
                            }
                    }
                }
                else{//PHASE DE BATAILLE
                    isUnits=true;
                    if(aff->event.type == SDL_MOUSEBUTTONDOWN){
                        for(int i=2;i<int(jeu.ennemyUnits.size())+2;i++){
                            if (float(aff->event.motion.x) >= aff->cartes[i].x && float(aff->event.motion.x) <=(aff->cartes[i].x+aff->cartes[i].w)
                            && float(aff->event.motion.y) >= aff->cartes[i].y && float(aff->event.motion.y)<= (aff->cartes[i].y+aff->cartes[i].h)){
                                if(aff->event.button.button == SDL_BUTTON_RIGHT){
                                    inputgame=i-1;
                                    std::cout<<"you selected the unit "<< inputgame<<std::endl;
                                    aff->idCard=i;
                                    aff->nameCard=jeu.ennemyUnits[inputgame-1].getName();
                                    cartSelect=true;
                                }
                            }
                        }
                    }
                    
                    if(cartSelect && aff->event.type == SDL_MOUSEBUTTONDOWN){
                        for(int iii = 0; iii < tailleG; ++iii) {
                            for(int jjj = 0; jjj < tailleG; ++jjj) {
                                if (float(aff->event.motion.x) >= aff->table[iii][jjj].x && float(aff->event.motion.x) <=(aff->table[iii][jjj].x+aff->table[iii][jjj].w)
                                && float(aff->event.motion.y) >= aff->table[iii][jjj].y && float(aff->event.motion.y)<= (aff->table[iii][jjj].y+aff->table[iii][jjj].h)){ 
                                    std::cout<< "x = "<<iii<<"  y = "<<jjj<<std::endl;
                                    if(inputgame > 0 && (unsigned int)inputgame <= jeu.ennemyUnits.size()){
                                        if(jeu.actUnit){
                                            std::cout << "a quelle case bouger l'unite?" << std::endl;
                                            jeu.xmove=iii;
                                            jeu.ymove=jjj;
                                            if(0 <= jeu.xmove && jeu.xmove < jeu.dim && 0 <= jeu.ymove && jeu.ymove < jeu.dim){
                                                if(!jeu.GB.getTable()[jeu.ymove*jeu.dim+jeu.xmove].isOccupied()){ //Si non occupé, on bouge
                                                   jeu.moveUnitEnnemy(inputgame);
                                                    aff->posx = iii;
                                                    aff->posy = jjj;
                                                    aff->cardDisplayed = true;
                                                }
                                                else {
                                                    jeu.attackByEnnemy(inputgame);
                                                }
                                            }
                                            else {std::cout << "position non valide dans le tableau, svp reesayer" << std::endl;}
                                        } 
                                    }
                                    else {std::cout << "input non reconnu, svp ressayer" << std::endl;}
                                    jeu.actUnit = true;
                                }
                            }
                        } 
                    }

                    //GESTION DU QUIT
                    if(aff->event.type == SDL_MOUSEBUTTONDOWN && float(aff->event.motion.x) >= aff->cartes[1].x && float(aff->event.motion.x) <=(aff->cartes[1].x+aff->cartes[1].w)
                    && float(aff->event.motion.y) >= aff->cartes[1].y && float(aff->event.motion.y)<= (aff->cartes[1].y+aff->cartes[1].h)){
                        inputgame=0;
                        std::cout<<"QUIT "<< inputgame<<std::endl;
                        aff->isRun=false;
                    }
                }
            }
    } 
   //std::cout<< aff->event.motion.x << " , "<<aff->event.motion.y<<std::endl;     
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
            if(input == -1 && aff->isMenu){

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
            }
            break;
        default:
            break;
     
    }   
}

void game2D::updategame2D(){
    while(aff->isRun){
        frameStart=SDL_GetTicks();
        menu2D();
        aff->menu2D();
        
        if(!isNOInit)typegame();
        if(jeu.playerTurn){
            if(!isUnits){
                aff->drawGame(tailleG,jeu.playerDeck.getSize(),cartSelect,jeu.playerTurn,jeu.playerUnits,jeu.ennemyUnits);
                
            }
            else aff->drawGame(tailleG,jeu.playerUnits.size(),cartSelect,playerTurn,jeu.playerUnits,jeu.ennemyUnits);
        }else{
            if(!isUnits)aff->drawGame(tailleG,jeu.ennemyDeck.getSize(),cartSelect,jeu.playerTurn,jeu.playerUnits,jeu.ennemyUnits);
        else aff->drawGame(tailleG,jeu.ennemyUnits.size(),cartSelect,jeu.playerTurn,jeu.playerUnits,jeu.ennemyUnits);
        }
    
        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

void game2D::cleangame2D(){
    aff->clean2D(jeu.playerDeck.getSize() );
    
    delete aff;
    aff = NULL;
}

game2D::~game2D(){

}



