#include "gameConsole.h"
#include<vector>
using namespace std;

bool gameConsole::getdeployphase() const{
    return deployPhase;
}

int getIndex(int x, int y, vector<unit> v) {
    int u = -1;
    for(int i = 0; i < (int)v.size(); i++) {
        if(v[i].getX() == x && v[i].getY() == y) {u = i;} 
    }
    return u;
}

void gameConsole::deployUnitPlayer(int input){
    if(!GB[0].isOccupied()){
        playerUnits.push_back(unit(playerDeck[input - 1], true)); // on insere la carte dans le tab d'unites
        GB[0].occupy(playerUnits.back()); // indique que la case est occupée (utile pour affichage console)
        playerUnits.back().setTo(0,0); // on initialise la position de l'unite
        playerDeck.supprimerCarte(input - 1); // on elimine la carte du deck
        deployPhase = !deployPhase;
    }
    else cout << "La base est deja occupée, deployer une unite est impossible" << endl;
}
void gameConsole::deployUnitEnnemy(int input){
    if(!GB[4 * dim + 4].isOccupied()){
        ennemyUnits.push_back(unit(ennemyDeck[input - 1], false));
        GB[(dim-1)*dim+dim-1].occupy(ennemyUnits.back()); // insere la piece choisice dans le table de jeu
        ennemyUnits.back().setTo(dim-1,dim-1);
        ennemyDeck.supprimerCarte(input - 1);
        deployPhase = !deployPhase;
    }
    else cout << "La base est deja occupée, deployer une unite est impossible" << endl;
}

void gameConsole::moveUnitPlayer(int input){
    easeUnit = playerUnits[input - 1]; // pour lisibilité
    if(playerUnits[input - 1].moveTo(xmove, ymove)){ //On bouge l'unite SI le range est correct
        GB[easeUnit.getY() * dim + easeUnit.getX()].deOccupy(); //on libere la case anterieur
        GB[ymove * dim + xmove].occupy(playerUnits[input - 1]);
        actUnit = false;
        deployPhase = !deployPhase;
        playerTurn = !playerTurn;
    }
}

void gameConsole::moveUnitEnnemy(int input){
    easeUnit = ennemyUnits[input - 1]; // pour lisibilité
    if(ennemyUnits[input - 1].moveTo(xmove, ymove)){
        GB.getTable()[easeUnit.getY() * dim + easeUnit.getX()].deOccupy(); //on deOccupe la case anterieur
        GB.getTable()[ymove * dim + xmove].occupy(ennemyUnits[input - 1]);
        actUnit = false;
        deployPhase = !deployPhase;
        playerTurn = !playerTurn;
    }
}

void gameConsole::attackByPlayer(int input){
    int index = getIndex(xmove, ymove, playerUnits);
    cout<< "esto vale el index" << index << endl;
    if(index > 0) { // Si l'unite est une unite alliée
    cout << "position deja occupée par une autre unite, svp reesayer" << endl;
    }
    else{
        if(playerUnits[input - 1].isInAtkRange(xmove, ymove)){ //vergas
            index = getIndex(xmove, ymove, ennemyUnits);
            cout << endl;
            cout << "********************" << endl;
            cout << "Initiating battle" << endl;
            cout << "********************" << endl;
            cout << endl;
            if(playerUnits[input - 1].battleUnit(ennemyUnits[index])){ // Si ennemi vaincu
                ennemyUnits.erase(ennemyUnits.begin() + index); // On elimine l'unite ennemie
                GB[playerUnits[input - 1].getY() * dim + playerUnits[input - 1].getX()].deOccupy(); //on deOccupe la case anterieur
                GB[ymove * dim + xmove].occupy(playerUnits[input - 1]);
                if(playerUnits[input - 1].getAtkRange() == 1) playerUnits[input - 1].setTo(xmove, ymove); // on update xpos et ypos l'unite
            }
            actUnit = false;
            deployPhase = !deployPhase;
            playerTurn = !playerTurn;
            checkForGameEnd();
        }
    }
}

void gameConsole::attackByEnnemy(int input){
    int index = getIndex(xmove, ymove, ennemyUnits);
    cout<<"esto vale el index" <<index<<endl;
    if(index > 0) { // Si l'unite est une unite alliée
    cout << "position deja occupée par une autre unite, svp reesayer" << endl;
    }
    else{
        if(ennemyUnits[input - 1].isInAtkRange(xmove, ymove)){
            index = getIndex(xmove, ymove, playerUnits);
            cout << "********************" << endl;
            cout << "Initiating battle" << endl;
            cout << "********************" << endl;
            if(ennemyUnits[input - 1].battleUnit(playerUnits[index])){ // Si ennemi vaincu
                playerUnits.erase(std::next(playerUnits.begin(), index - 1)); // On elimine l'unite ennemie
                GB.getTable()[ennemyUnits[input - 1].getY() * dim + ennemyUnits[input - 1].getX()].deOccupy(); //on deOccupe la case anterieur
                GB.getTable()[ymove * dim + xmove].occupy(ennemyUnits[input - 1]);
                ennemyUnits[input - 1].setTo(xmove, ymove); // on update xpos et ypos l'unite
            }
            actUnit = false;
            deployPhase = !deployPhase;
            playerTurn = !playerTurn;
            checkForGameEnd();
        }
        else{
            cout << "Unit out of attack range" << endl;
        }
    }
}

void gameConsole::updateStatusPlayer(){
    cout << "entered updateStatus" << endl;
    for(int i = 0; i < (int)playerUnits.size(); i++){
        cout << "checked " << i << " units for status" << endl;
        for(int j = 0; j < playerUnits[i].getAppliedSize(); j++){
            cout << "checked " << j << " statuses" << endl;
            if(playerUnits[i].getAppliedStatus(j).statIndex > -1){
                playerUnits[i].applyStatus(sCodex[playerUnits[i].getAppliedStatus(j).statIndex]);
                playerUnits[i].getAppliedStatus(j).statStrength += -1;
                if(playerUnits[i].getAppliedStatus(j).statStrength == 0){
                    playerUnits[i].eraseAppliedStatus(j);
                }
            }
        }
    }
}

void gameConsole::updateStatusEnnemy(){
    cout << "entered updateStatus" << endl;
    for(int i = 0; i < (int)ennemyUnits.size(); i++){
        cout << "checked " << i << "units for status" << endl;
        for(int j = 0; j < ennemyUnits[i].getAppliedSize(); j++){
            cout << "checked " << j << "statuses" << endl;
            ennemyUnits[i].applyStatus(sCodex[ennemyUnits[i].getAppliedStatus(j).statIndex]);
        }
    }
}

void gameConsole::checkForGameEnd(){
    if(!playerUnits[0].itsChamp()) triggerVictory(false); //victoire joueur
    if(!ennemyUnits[0].itsChamp()) triggerVictory(true); //victoire ennemy
    cout << "checked game end" << endl;
}

void gameConsole::triggerVictory(bool player){
    stay = false;
    if(player){
        cout << "Victoire de joueur Player (joueur 1)!" << endl;
    }
    else{
        cout << "Victoire de joueur Ennemy (joueur 2)!" << endl;
    }
}

void gameConsole::triggerDraw(){

}

gameConsole::gameConsole(){}
gameConsole::~gameConsole(){}

void gameConsole::gameInit(unsigned int xdim, unsigned int ydim){
    GB.init(5,5); //creation du tableau de jeu
    defaultPieces.fillLibrary("./assets/units.txt");
    playerDeck.fillLibrary("./assets/userDeck.txt");
    ennemyDeck.fillLibrary("./assets/userDeck.txt");
    sCodex.init("./assets/statusCodex.txt");
    cout << "Size of playerDeck = " << playerDeck.getSize() << endl;
    cout << "Size of defaultLib = " << defaultPieces.getSize() << endl;
    std::cout << "Creation des Decks et du tableau de Jeu fait" << std::endl;
    int champIndex = playerDeck.getChampIndex();
    playerUnits.push_back(unit(playerDeck[champIndex], playerTurn));
    playerDeck.supprimerCarte(champIndex);
    champIndex = ennemyDeck.getChampIndex();
    ennemyUnits.push_back(unit(ennemyDeck[champIndex], !playerTurn));
    ennemyDeck.supprimerCarte(champIndex);
    playerUnits[0].setTo(0, 1);
    ennemyUnits[0].setTo(4, 3);
    GB[1 * dim + 0].occupy(playerUnits[0]);
    GB[3 * dim + 4].occupy(ennemyUnits[0]);
    GB.afficherConsole();
    cout << "************************" << endl;
    cout << "case de player occupe: " << GB[1*dim].isOccupied() << endl;
    cout << "case de ennemy occupe: " << GB[3*dim+4].isOccupied() << endl;
}

void gameConsole::gameInitServer(unsigned int xdim, unsigned int ydim){
    
    GB.init(5,5); //creation du tableau de jeu
    defaultPieces.fillLibrary("./assets/units.txt"); 
    playerDeck.fillLibrary("./assets/userDeck.txt");
    ennemyDeck.fillLibrary("./assets/userDeck.txt");
    sCodex.init("./assets/statusCodex.txt");
    int champIndex = playerDeck.getChampIndex();
    playerUnits.push_back(unit(playerDeck[champIndex], playerTurn));
    playerDeck.supprimerCarte(champIndex);
    ennemyUnits.push_back(unit(playerDeck[champIndex], !playerTurn));
    ennemyDeck.supprimerCarte(champIndex);
    GB.afficherConsole();
    sv.serverInit();
}

void gameConsole::gameInitClient(unsigned int xdim, unsigned int ydim, char *arg1, int arg2){
    
    GB.init(5,5); //creation du tableau de jeu
    defaultPieces.fillLibrary("./assets/units.txt"); 
    playerDeck.fillLibrary("./assets/userDeck.txt");
    ennemyDeck.fillLibrary("./assets/userDeck.txt");
    sCodex.init("./assets/statusCodex.txt");
    int champIndex = playerDeck.getChampIndex();
    playerUnits.push_back(unit(playerDeck[champIndex], playerTurn));
    playerDeck.supprimerCarte(champIndex);
    ennemyUnits.push_back(unit(playerDeck[champIndex], !playerTurn));
    ennemyDeck.supprimerCarte(champIndex);
    GB.afficherConsole();
    cl.clientInit(arg1,arg2);
}

void gameConsole::gameAfficher(){
    string defLine = "[ "; //Creation d'une ligne du tab en fonction des dimensions
    for(int i = 0; i < GB.getX(); i++){
        defLine.append("### ");
    }
    //defLine = [ ### ### ### ### ### ]
    defLine.append("]");
    for(int j = 0; j < GB.getY(); j++){
        tableLine = defLine;
    }
}

//Esto no sirve pa na
/*void gameConsole::gameHandleEvents(){
    unsigned int y= 1;
    if(playerTurn){
        cout << "PLAYER 1 TURN" << endl;
        if(deployPhase){ // DEPLOYMENT PHASE (ESTA EN INGLES PQ NO SE COMO DECIRLO EN FRANCES)
            cout << "cartes disponibles: " << endl;
            playerDeck.afficher();
            cout << "quelle carte voulez vous jouer? - tapez 0 pour abandoner le jeu sinon le # de la carte, 100 pour passer" << endl;
            cin >> input;
        }
        else{ // PHASE DE BATAILLE
            cout << "unites disponibles: " << endl;
            for(auto i = playerUnits.begin(); i != playerUnits.end(); i++){
                cout << y << ". ";
                (*i).afficherConsole();
                y++;
            }
            cout << "quelle carte voulez vous utiliser? - tapez 0 pour abandoner le jeu sinon le # de la carte" << endl;
            cin >> input;
            cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
            do{
                cin >> xmove;
                cin >> ymove;
                if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                    actUnit = false;
                }
                else{
                    cout << "Position non valide svp reesayer" << endl;
                }
            }while(actUnit);
        }
    }
    else{
        cout << "PLAYER 2 TURN" << endl;
        if(deployPhase){ // DEPLOYMENT PHASE (ESTA EN INGLES PQ NO SE COMO DECIRLO EN FRANCES)
            cout << "cartes disponibles: " << endl;
            for(auto i = ennemyDeck.begin(); i != ennemyDeck.end(); i++){
                cout << y << ". ";
                (*i).afficherConsole();
                y++;
            }
            cout << "quelle carte voulez vous jouer? - tapez 0 pour abandoner le jeu sinon le # de la carte, 100 pour passer" << endl;
            cin >> input;
        }
        else{ // PHASE DE BATAILLE
            cout << "unites disponibles: " << endl;
            for(auto i = ennemyUnits.begin(); i != ennemyUnits.end(); i++){
                cout << y << ". ";
                (*i).afficherConsole();
                y++;
            }
            cout << "quelle carte voulez vous utiliser? - tapez 0 pour abandoner le jeu sinon le # de la carte" << endl;
            cin >> input;
            cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
            do{
                cin >> xmove;
                cin >> ymove;
                if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                    actUnit = false;
                }
                else{
                    cout << "Position non valide svp reesayer" << endl;
                }
            }while(actUnit);
        }
    }
}*/
//funcion inutil ^
// eh hpta q si funciona no necesitamos copiar y pegar las 400 lineas de codigo de mierda

void gameConsole::gameUpdate(){
    unsigned int y = 1;
    GB.afficherConsole();
    while(stay){
        if(playerTurn){
            cout << "********************" << endl;
            cout << "PLAYER TURN" << endl;
            cout << "********************" << endl;
            cout << endl;
            updateStatusPlayer();
            cout << "PASS THIS SHIT" << endl;
            if(deployPhase){ //DEPLOYMENT PHASE
                cout << "cartes disponibles: " << endl;
                playerDeck.afficher();
                cout <<"deck size = "<< playerDeck.getSize() << endl;
                cout << "quelle carte voulez vous jouer? - tapez 0 pour abandoner le jeu sinon le # de la carte, 100 pour passer" << endl;
                cin >> input;
                switch(input){
                    case 0:
                        stay = false;
                        break;
                    case 100:
                        if(playerUnits.size() > 0){
                            deployPhase = !deployPhase; 
                        }
                        else { 
                            cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << endl;
                            cin >> input;
                        }
                        break;
                    default:
                        if(input > 0 && input <= playerDeck.getSize()){
                            deployUnitPlayer(input);
                        }
                        else {cout << "input non reconnu, svp ressayer" << endl;}
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
            else{ // PHASE DE BATAILLE
                cout << "unites disponibles: " << endl;
                for(auto i = playerUnits.begin(); i != playerUnits.end(); i++){
                    cout << y << ". ";
                    (*i).afficherConsole();
                    y++;
                }
                cout << "quelle carte voulez vous utiliser? - tapez 0 pour abandoner le jeu sinon le # de la carte" << endl;
                cout <<"playerdeck size = "<< playerUnits.size() << endl;
                cin >> input;
                switch(input){
                    case 0:
                        stay = false;
                        break;
                    default:
                        if(input > 0 && (unsigned int)input <= playerUnits.size()){
                        while(actUnit){
                            cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
                            cin >> xmove;
                            cin >> ymove;
                            if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                                if(!GB.getTable()[ymove*dim+xmove].isOccupied()){ //Si non occupé, on bouge
                                    moveUnitPlayer(input);
                                }
                                else {
                                    attackByPlayer(input);
                                }
                            }
                            else {cout << "position non valide dans le tableau, svp reesayer" << endl;}
                            } 
                        }
                        else {cout << "input non reconnu, svp ressayer" << endl;}
                        actUnit = true;
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
        }
        else{ // ENNEMY TURN
            cout << "********************" << endl;
            cout << "ENNEMY TURN" << endl;
            cout << "********************" << endl;
            updateStatusEnnemy();
            if(deployPhase){ //DEPLOYMENT PHASE
                cout << "cartes disponibles: " << endl;
                ennemyDeck.afficher();
                cout <<"deck size = "<< ennemyDeck.getSize() << endl;
                cout << "quelle carte voulez vous jouer? - tapez 0 pour abandoner le jeu sinon le # de la carte, 100 pour passer" << endl;
                cin >> input;
                switch(input){
                    case 0:
                        stay = false;
                        break;
                    case 100:
                    if(ennemyUnits.size() > 0){
                            deployPhase = !deployPhase; 
                            break;
                        } else { 
                            cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << endl;
                            cin >> input;
                            }
                    default:
                        if(input > 0 && input <= ennemyDeck.getSize()){
                            if(!GB.getTable()[4 * dim + 4].isOccupied()){
                                deployUnitEnnemy(input);
                            }
                            else cout << "La base est deja occupée, deployer une unite est impossible" << endl;
                        }
                        else {cout << "input non reconnu, svp ressayer" << endl;}
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
            else{ //PHASE DE BATAILLE
                cout << "unites disponibles: " << endl;
                for(auto i = ennemyUnits.begin(); i != ennemyUnits.end(); i++){
                    cout << y << ". ";
                    (*i).afficherConsole();
                    y++;
                }
                cout << "quelle carte voulez vous utiliser? - tapez 0 pour abandoner le jeu sinon le # de la carte" << endl;
                cin >> input;
                switch(input){
                    case 0:
                        stay = false;
                        break;
                    default:
                        cout <<"playerdeck size = "<< ennemyUnits.size() << endl;
                        if(input > 0 && (unsigned int)input <= ennemyUnits.size()){
                        while(actUnit){
                            cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
                            cin >> xmove;
                            cin >> ymove;
                            if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                                if(!GB.getTable()[ymove*dim+xmove].isOccupied()){ //Si case vide
                                    moveUnitEnnemy(input);
                                }
                                else {
                                    attackByEnnemy(input);
                                }
                            }
                            else {cout << "position non valide dans le tableau, svp reesayer" << endl;}
                        } 
                        }
                        else {cout << "input non reconnu, svp ressayer" << endl;}
                        actUnit = true;
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
        }
    }
    GB.afficherConsole();
}


void gameConsole::gameUpdateNET(){
    unsigned int y = 1;
    GB.afficherConsole();
    while(stay){
        /* This check the sd if there is a pending connection. * If there is one, accept that, and open a new socket for communicating */ 
        
        if ((sv.csd1 = SDLNet_TCP_Accept(sv.sd)) ) { 
            
            if ((sv.remoteIP = SDLNet_TCP_GetPeerAddress(sv.csd1))) 
            /* Print the address, converting in the host format */ 
            std::cout << "Host connected: " << SDLNet_Read32(&sv.remoteIP->host) << SDLNet_Read16(&sv.remoteIP->port) << std::endl;
            else std::cerr << stderr << "SDLNet_TCP_GetPeerAddress: " << SDLNet_GetError() << std::endl;

            sv.quit2=0;
            while(!sv.quit2){
                //First player
                if(playerTurn){
                    cout << "********************" << endl;
                    cout << "PLAYER 1" << endl;
                    cout << "********************" << endl;
                    cout << endl;
                    if(deployPhase){ //DEPLOYMENT PHASE
                        cout << "cartes disponibles: " << endl;
                        playerDeck.afficher();
                        cout <<"deck size = "<< playerDeck.getSize() << endl;
                        cout << "quelle carte voulez vous jouer? - tapez 0 pour abandoner le jeu sinon le # de la carte, 100 pour passer" << endl;
                        cin >> sv.buffer2;
                        input=(int)*sv.buffer2 - 48;
                        cout<<"esto vale input = "<<input<<endl;
                        sv.Send();
                        switch(input){
                            case 0:
                                sv.quit2 = 1;
                                sv.Close();
                                stay = false;
                                break;
                            case 100:
                                if(playerUnits.size() > 0){
                                    deployPhase = !deployPhase; 
                                } else { 
                                    cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << endl;
                                    cin >> sv.buffer2;
                                    input=(int)*sv.buffer2 - 48;
                                    sv.Send();
                                    }
                                break;
                            default:
                                if(input > 0 && input <= playerDeck.getSize()){
                                    deployUnitPlayer(input);
                                }
                                else {cout << "input non reconnu, svp ressayer" << endl;}
                                GB.afficherConsole();
                                break;
                        }
                        y = 1;
                    }
                    else{ // PHASE DE BATAILLE
                        cout << "unites disponibles: " << endl;
                        for(auto i = playerUnits.begin(); i != playerUnits.end(); i++){
                            cout << y << ". ";
                            (*i).afficherConsole();
                            y++;
                        }
                        cout << "quelle carte voulez vous utiliser? - tapez 0 pour abandoner le jeu sinon le # de la carte" << endl;
                        cout <<"playerdeck size = "<< playerUnits.size() << endl;
                        cin >> sv.buffer2;
                        input=(int)*sv.buffer2 -48;
                        sv.Send();
                        switch(input){
                            case 0:
                                sv.quit2 = 1;
                                sv.Close();
                                stay = false;
                                break;
                            default:
                                if(input > 0 && (unsigned int)input <= playerUnits.size()){
                                while(actUnit){
                                    cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
                                    cin >> sv.buffer2;
                                    xmove = (int)*sv.buffer2-48;
                                    sv.Send();
                                    cin >> sv.buffer2;
                                    ymove = (int)*sv.buffer2-48;
                                    sv.Send();
                                    if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                                        if(!GB.getTable()[ymove*dim+xmove].isOccupied()){ //Si non occupé, on bouge
                                                moveUnitPlayer(input);
                                        }
                                        else {
                                                attackByPlayer(input);
                                        }
                                            
                                    }
                                    else {cout << "position non valide dans le tableau, svp reesayer" << endl;}
                                } 
                                }
                                else {cout << "input non reconnu, svp ressayer" << endl;}
                                actUnit = true;
                                GB.afficherConsole();
                                break;
                        }
                        y = 1;
                    }
                }
                else{ // ENNEMY TURN
                    cout << "********************" << endl;
                    cout << "Player 2" << endl;
                    cout << "********************" << endl;
                    if(deployPhase){ //DEPLOYMENT PHASE
                        sv.Receive();
                        input = (int)*sv.buffer1-48;
                        switch(input){
                            case 0:
                                sv.quit2 = 1;
                                sv.Close();
                                stay = false;
                                break;
                            case 100:
                            if(ennemyUnits.size() > 0){
                                    deployPhase = !deployPhase; 
                                    break;
                                } else { 
                                    //cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << endl;
                                    sv.Receive();
                                    input = (int)*sv.buffer1-48;
                                    }
                            default:
                                if(input > 0 && input <= ennemyDeck.getSize()){
                                    if(!GB.getTable()[4 * dim + 4].isOccupied()){
                                        deployUnitEnnemy(input);
                                    }
                                    else cout << "Waiting for the client..." << endl;
                                }
                                else {cout << "Waiting for the client..." << endl;}
                                GB.afficherConsole();
                                break;
                        }
                        y = 1;
                    }
                    else{ //PHASE DE BATAILLE
                        sv.Receive();
                        input = (int)*sv.buffer1-48;
                        switch(input){
                            case 0:
                                sv.quit2 = 1;
                                sv.Close();
                                stay = false;
                                break;
                            default:
                                if(input > 0 && (unsigned int)input <= ennemyUnits.size()){
                                while(actUnit){
                                    sv.Receive();
                                    xmove = (int)*sv.buffer1-48;
                                    sv.Receive();
                                    ymove = (int)*sv.buffer1-48;
                                    if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                                        if(!GB.getTable()[ymove*dim+xmove].isOccupied()){ //Si case vide
                                               moveUnitEnnemy(input);
                                        }
                                        else {
                                                attackByEnnemy(input);
                                        }
                                    }
                                    else {cout << "Waiting for the client..." << endl;}
                                } 
                                }
                                else {cout << "Waiting for the client..." << endl;}
                                actUnit = true;
                                GB.afficherConsole();
                                break;
                        }
                        y = 1;
                    }
                }
            }
        /* Close the client socket */
        SDLNet_TCP_Close(sv.csd1);
        }
    }
    GB.afficherConsole();
    sv.Close();
}

void gameConsole::gameUpdateNETClient(){
    unsigned int y = 1;
    GB.afficherConsole();
    while(stay){
        if(playerTurn){
            cout << "********************" << endl;
            cout << "PLAYER 1 TURN" << endl;
            cout << "********************" << endl;
            cout << endl;
            if(deployPhase){ //DEPLOYMENT PHASE
                cl.Receive();
                input = (int)*cl.buffer2-48;
                switch(input){
                    case 0:
                        stay = false;
                        sv.Close();
                        break;
                    case 100:
                        if(playerUnits.size() > 0){
                            deployPhase = !deployPhase; 
                        } else { 
                            //cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << endl;
                            cl.Receive();
                            input = (int)*cl.buffer2-48;
                            }
                        break;
                    default:
                        if(input > 0 && input <= playerDeck.getSize()){
                            deployUnitPlayer(input);
                        }
                        else {cout << "Waiting for the server..." << endl;}
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
            else{ // PHASE DE BATAILLE
                cl.Receive();
                input = (int)*cl.buffer2-48;
                switch(input){
                    case 0:
                        sv.Close();
                        stay = false;
                        break;
                    default:
                        if(input > 0 && (unsigned int)input <= playerUnits.size()){
                        while(actUnit){
                            //cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
                            cl.Receive();
                            xmove = (int)*cl.buffer2-48;
                            cl.Receive();
                            ymove = (int)*cl.buffer2-48;
                            if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                                if(!GB.getTable()[ymove*dim+xmove].isOccupied()){ //Si non occupé, on bouge
                                        moveUnitPlayer(input);
                                }
                                else {
                                        attackByPlayer(input);
                                }
                            }
                            else {cout << "Waiting for the server..." << endl;}
                            } 
                        }
                        else {cout << "Waiting for the server..." << endl;}
                        actUnit = true;
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
        }
        else{ // ENNEMY TURN
            cout << "********************" << endl;
            cout << "Player 2 TURN" << endl;
            cout << "********************" << endl;
            if(deployPhase){ //DEPLOYMENT PHASE
                cout << "cartes disponibles: " << endl;
                for(int i = 0; i < ennemyDeck.getSize(); i++){
                    cout << y << ". ";
                    ennemyDeck[i].afficherConsole();
                    y++;
                }
                cout <<"deck size = "<< ennemyDeck.getSize() << endl;
                cout << "quelle carte voulez vous jouer? - tapez 0 pour abandoner le jeu sinon le # de la carte, 100 pour passer" << endl;
                cin >> cl.buffer;
                input = (int)*cl.buffer-48;
                cl.Send();
                switch(input){
                    case 0:
                        sv.Close();
                        stay = false;
                        break;
                    case 100:
                    if(ennemyUnits.size() > 0){
                            deployPhase = !deployPhase; 
                            break;
                        } else { 
                            cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << endl;
                            cin >> cl.buffer;
                            input = (int)*cl.buffer-48;
                            cl.Send();
                            }
                    default:
                        if(input > 0 && input <= ennemyDeck.getSize()){
                            if(!GB.getTable()[4 * dim + 4].isOccupied()){
                                deployUnitEnnemy(input);
                            }
                            else cout << "La base est deja occupée, deployer une unite est impossible" << endl;
                        }
                        else {cout << "input non reconnu, svp ressayer" << endl;}
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
            else{ //PHASE DE BATAILLE
                cout << "unites disponibles: " << endl;
                for(auto i = ennemyUnits.begin(); i != ennemyUnits.end(); i++){
                    cout << y << ". ";
                    (*i).afficherConsole();
                    y++;
                }
                cout << "quelle carte voulez vous utiliser? - tapez 0 pour abandoner le jeu sinon le # de la carte" << endl;
                cin >> cl.buffer;
                input = (int)*cl.buffer-48;
                cl.Send();
                switch(input){
                    case 0:
                        sv.Close();
                        stay = false;
                        break;
                    default:
                        cout <<"playerdeck size = "<< ennemyUnits.size() << endl;
                        if(input > 0 && (unsigned int)input <= ennemyUnits.size()){
                        while(actUnit){
                            cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
                            cin >> cl.buffer;
                            xmove = (int)*cl.buffer-48;
                            cl.Send();
                            cin >> cl.buffer;
                            ymove = (int)*cl.buffer-48;
                            cl.Send();
                            if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                                if(!GB.getTable()[ymove*dim+xmove].isOccupied()){ //Si case vide
                                        moveUnitEnnemy(input);
                                }
                                else {
                                    attackByEnnemy(input);
                                }
                            }
                            else {cout << "position non valide dans le tableau, svp reesayer" << endl;}
                        } 
                        }
                        else {cout << "input non reconnu, svp ressayer" << endl;}
                        actUnit = true;
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
        }
    }
    GB.afficherConsole();
    cl.Close();
}

bool gameConsole::Stay(){return stay;}

//no me vas a mover esto o te parto

void gameConsole::gameUpdateNO(){
    unsigned int y = 1;
    GB.afficherConsole();
    if(playerTurn){
            cout << "********************" << endl;
            cout << "PLAYER TURN" << endl;
            cout << "********************" << endl;
            cout << endl;
            if(deployPhase){ //DEPLOYMENT PHASE
                cout << "cartes disponibles: " << endl;
                for(int i = 0; i < playerDeck.getSize(); i++){
                    cout << y << ". ";
                    playerDeck[i].afficherConsole();
                    y++;
                }
                cout <<"deck size = "<< playerDeck.getSize() << endl;
                cout << "quelle carte voulez vous jouer? - tapez 0 pour abandoner le jeu sinon le # de la carte, 100 pour passer" << endl;
                cin >> input;
                switch(input){
                    case 0:
                        stay = false;
                        break;
                    case 100:
                        if(playerUnits.size() > 0){
                            deployPhase = !deployPhase; 
                        } else { 
                            cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << endl;
                            cin >> input;
                            }
                        break;
                    default:
                        if(input > 0 && input <= playerDeck.getSize()){
                            deployUnitPlayer(input);
                        }
                        else {cout << "input non reconnu, svp ressayer" << endl;}
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
            else{ // PHASE DE BATAILLE
                cout << "unites disponibles: " << endl;
                for(auto i = playerUnits.begin(); i != playerUnits.end(); i++){
                    cout << y << ". ";
                    (*i).afficherConsole();
                    y++;
                }
                cout << "quelle carte voulez vous utiliser? - tapez 0 pour abandoner le jeu sinon le # de la carte" << endl;
                cout <<"playerdeck size = "<< playerUnits.size() << endl;
                cin >> input;
                switch(input){
                    case 0:
                        stay = false;
                        break;
                    default:
                        if(input > 0 && (unsigned int)input <= playerUnits.size()){
                        while(actUnit){
                            cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
                            cin >> xmove;
                            cin >> ymove;
                            if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                                if(!GB.getTable()[ymove*dim+xmove].isOccupied()){ //Si non occupé, on bouge
                                    moveUnitPlayer(input);
                                }
                                else {
                                    attackByPlayer(input);
                                }
                            }
                            else {cout << "position non valide dans le tableau, svp reesayer" << endl;}
                            } 
                        }
                        else {cout << "input non reconnu, svp ressayer" << endl;}
                        actUnit = true;
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
        }
        else{ // ENNEMY TURN
            cout << "********************" << endl;
            cout << "ENNEMY TURN" << endl;
            cout << "********************" << endl;
            if(deployPhase){ //DEPLOYMENT PHASE
                cout << "cartes disponibles: " << endl;
                for(int i = 0; i < ennemyDeck.getSize(); i++){
                    cout << y << ". ";
                    ennemyDeck[i].afficherConsole();
                    y++;
                }
                cout <<"deck size = "<< ennemyDeck.getSize() << endl;
                cout << "quelle carte voulez vous jouer? - tapez 0 pour abandoner le jeu sinon le # de la carte, 100 pour passer" << endl;
                cin >> input;
                switch(input){
                    case 0:
                        stay = false;
                        break;
                    case 100:
                    if(ennemyUnits.size() > 0){
                            deployPhase = !deployPhase; 
                            break;
                        } else { 
                            cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << endl;
                            cin >> input;
                            }
                    default:
                        if(input > 0 && input <= ennemyDeck.getSize()){
                            if(!GB.getTable()[4 * dim + 4].isOccupied()){
                                deployUnitEnnemy(input);
                            }
                            else cout << "La base est deja occupée, deployer une unite est impossible" << endl;
                        }
                        else {cout << "input non reconnu, svp ressayer" << endl;}
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
            else{ //PHASE DE BATAILLE
                cout << "unites disponibles: " << endl;
                for(auto i = ennemyUnits.begin(); i != ennemyUnits.end(); i++){
                    cout << y << ". ";
                    (*i).afficherConsole();
                    y++;
                }
                cout << "quelle carte voulez vous utiliser? - tapez 0 pour abandoner le jeu sinon le # de la carte" << endl;
                cin >> input;
                switch(input){
                    case 0:
                        stay = false;
                        break;
                    default:
                        cout <<"playerdeck size = "<< ennemyUnits.size() << endl;
                        if(input > 0 && (unsigned int)input <= ennemyUnits.size()){
                        while(actUnit){
                            cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
                            cin >> xmove;
                            cin >> ymove;
                            if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                                if(!GB.getTable()[ymove*dim+xmove].isOccupied()){ //Si case vide
                                    moveUnitEnnemy(input);
                                }
                                else {
                                    attackByEnnemy(input);
                                }
                            }
                            else {cout << "position non valide dans le tableau, svp reesayer" << endl;}
                        } 
                        }
                        else {cout << "input non reconnu, svp ressayer" << endl;}
                        actUnit = true;
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
        }
    GB.afficherConsole();
}



void gameConsole::gameUpdateNETNO(){
    unsigned int y = 1;
    GB.afficherConsole();
        /* This check the sd if there is a pending connection. * If there is one, accept that, and open a new socket for communicating */ 
        
        if ((sv.csd1 = SDLNet_TCP_Accept(sv.sd)) ) { 
            
            if ((sv.remoteIP = SDLNet_TCP_GetPeerAddress(sv.csd1))) 
            /* Print the address, converting in the host format */ 
            std::cout << "Host connected: " << SDLNet_Read32(&sv.remoteIP->host) << SDLNet_Read16(&sv.remoteIP->port) << std::endl;
            else std::cerr << stderr << "SDLNet_TCP_GetPeerAddress: " << SDLNet_GetError() << std::endl;

            sv.quit2=0;
            while(!sv.quit2){
                //First player
                if(playerTurn){
                    cout << "********************" << endl;
                    cout << "PLAYER 1" << endl;
                    cout << "********************" << endl;
                    cout << endl;
                    if(deployPhase){ //DEPLOYMENT PHASE
                        cout << "cartes disponibles: " << endl;
                        for(int i = 0; i < playerDeck.getSize(); i++){
                            cout << y << ". ";
                            playerDeck[i].afficherConsole();
                            y++;
                        }
                        cout <<"deck size = "<< playerDeck.getSize() << endl;
                        cout << "quelle carte voulez vous jouer? - tapez 0 pour abandoner le jeu sinon le # de la carte, 100 pour passer" << endl;
                        cin >> sv.buffer2;
                        input=(int)*sv.buffer2 - 48;
                        cout<<"esto vale input = "<<input<<endl;
                        sv.Send();
                        switch(input){
                            case 0:
                                sv.quit2 = 1;
                                stay = false;
                                break;
                            case 100:
                                if(playerUnits.size() > 0){
                                    deployPhase = !deployPhase; 
                                } else { 
                                    cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << endl;
                                    cin >> sv.buffer2;
                                    input=(int)*sv.buffer2 - 48;
                                    sv.Send();
                                    }
                                break;
                            default:
                                if(input > 0 && input <= playerDeck.getSize()){
                                    deployUnitPlayer(input);
                                }
                                else {cout << "input non reconnu, svp ressayer" << endl;}
                                GB.afficherConsole();
                                break;
                        }
                        y = 1;
                    }
                    else{ // PHASE DE BATAILLE
                        cout << "unites disponibles: " << endl;
                        for(auto i = playerUnits.begin(); i != playerUnits.end(); i++){
                            cout << y << ". ";
                            (*i).afficherConsole();
                            y++;
                        }
                        cout << "quelle carte voulez vous utiliser? - tapez 0 pour abandoner le jeu sinon le # de la carte" << endl;
                        cout <<"playerdeck size = "<< playerUnits.size() << endl;
                        cin >> sv.buffer2;
                        input=(int)*sv.buffer2 -48;
                        sv.Send();
                        switch(input){
                            case 0:
                                sv.quit2 = 1;
                                stay = false;
                                break;
                            default:
                                if(input > 0 && (unsigned int)input <= playerUnits.size()){
                                while(actUnit){
                                    cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
                                    cin >> sv.buffer2;
                                    xmove = (int)*sv.buffer2-48;
                                    sv.Send();
                                    cin >> sv.buffer2;
                                    ymove = (int)*sv.buffer2-48;
                                    sv.Send();
                                    if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                                        if(!GB.getTable()[ymove*dim+xmove].isOccupied()){ //Si non occupé, on bouge
                                                moveUnitPlayer(input);
                                        }
                                        else {
                                                attackByPlayer(input);
                                        }
                                            
                                    }
                                    else {cout << "position non valide dans le tableau, svp reesayer" << endl;}
                                } 
                                }
                                else {cout << "input non reconnu, svp ressayer" << endl;}
                                actUnit = true;
                                GB.afficherConsole();
                                break;
                        }
                        y = 1;
                    }
                }
                else{ // ENNEMY TURN
                    cout << "********************" << endl;
                    cout << "Player 2" << endl;
                    cout << "********************" << endl;
                    if(deployPhase){ //DEPLOYMENT PHASE
                        sv.Receive();
                        input = (int)*sv.buffer1-48;
                        switch(input){
                            case 0:
                                sv.quit2 = 1;
                                stay = false;
                                break;
                            case 100:
                            if(ennemyUnits.size() > 0){
                                    deployPhase = !deployPhase; 
                                    break;
                                } else { 
                                    //cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << endl;
                                    sv.Receive();
                                    input = (int)*sv.buffer1-48;
                                    }
                            default:
                                if(input > 0 && input <= ennemyDeck.getSize()){
                                    if(!GB.getTable()[4 * dim + 4].isOccupied()){
                                        deployUnitEnnemy(input);
                                    }
                                    else cout << "Waiting for the client..." << endl;
                                }
                                else {cout << "Waiting for the client..." << endl;}
                                GB.afficherConsole();
                                break;
                        }
                        y = 1;
                    }
                    else{ //PHASE DE BATAILLE
                        sv.Receive();
                        input = (int)*sv.buffer1-48;
                        switch(input){
                            case 0:
                                sv.quit2 = 1;
                                stay = false;
                                break;
                            default:
                                if(input > 0 && (unsigned int)input <= ennemyUnits.size()){
                                while(actUnit){
                                    sv.Receive();
                                    xmove = (int)*sv.buffer1-48;
                                    sv.Receive();
                                    ymove = (int)*sv.buffer1-48;
                                    if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                                        if(!GB.getTable()[ymove*dim+xmove].isOccupied()){ //Si case vide
                                               moveUnitEnnemy(input);
                                        }
                                        else {
                                                attackByEnnemy(input);
                                        }
                                    }
                                    else {cout << "Waiting for the client..." << endl;}
                                } 
                                }
                                else {cout << "Waiting for the client..." << endl;}
                                actUnit = true;
                                GB.afficherConsole();
                                break;
                        }
                        y = 1;
                    }
                }
            }
        /* Close the client socket */
        SDLNet_TCP_Close(sv.csd1);
        }
    GB.afficherConsole();
    sv.Close();
}

void gameConsole::gameUpdateNETClientNO(){
    unsigned int y = 1;
    GB.afficherConsole();
    
        if(playerTurn){
            cout << "********************" << endl;
            cout << "PLAYER 1 TURN" << endl;
            cout << "********************" << endl;
            cout << endl;
            if(deployPhase){ //DEPLOYMENT PHASE
                cl.Receive();
                input = (int)*cl.buffer2-48;
                switch(input){
                    case 0:
                        stay = false;
                        break;
                    case 100:
                        if(playerUnits.size() > 0){
                            deployPhase = !deployPhase; 
                        } else { 
                            //cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << endl;
                            cl.Receive();
                            input = (int)*cl.buffer2-48;
                            }
                        break;
                    default:
                        if(input > 0 && input <= playerDeck.getSize()){
                            deployUnitPlayer(input);
                        }
                        else {cout << "Waiting for the server..." << endl;}
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
            else{ // PHASE DE BATAILLE
                cl.Receive();
                input = (int)*cl.buffer2-48;
                switch(input){
                    case 0:
                        stay = false;
                        break;
                    default:
                        if(input > 0 && (unsigned int)input <= playerUnits.size()){
                        while(actUnit){
                            //cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
                            cl.Receive();
                            xmove = (int)*cl.buffer2-48;
                            cl.Receive();
                            ymove = (int)*cl.buffer2-48;
                            if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                                if(!GB.getTable()[ymove*dim+xmove].isOccupied()){ //Si non occupé, on bouge
                                        moveUnitPlayer(input);
                                }
                                else {
                                        attackByPlayer(input);
                                }
                            }
                            else {cout << "Waiting for the server..." << endl;}
                            } 
                        }
                        else {cout << "Waiting for the server..." << endl;}
                        actUnit = true;
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
        }
        else{ // ENNEMY TURN
            cout << "********************" << endl;
            cout << "Player 2 TURN" << endl;
            cout << "********************" << endl;
            if(deployPhase){ //DEPLOYMENT PHASE
                cout << "cartes disponibles: " << endl;
                for(int i = 0; i < ennemyDeck.getSize(); i++){
                    cout << y << ". ";
                    ennemyDeck[i].afficherConsole();
                    y++;
                }
                cout <<"deck size = "<< ennemyDeck.getSize() << endl;
                cout << "quelle carte voulez vous jouer? - tapez 0 pour abandoner le jeu sinon le # de la carte, 100 pour passer" << endl;
                cin >> cl.buffer;
                input = (int)*cl.buffer-48;
                cl.Send();
                switch(input){
                    case 0:
                        stay = false;
                        break;
                    case 100:
                    if(ennemyUnits.size() > 0){
                            deployPhase = !deployPhase; 
                            break;
                        } else { 
                            cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << endl;
                            cin >> cl.buffer;
                            input = (int)*cl.buffer-48;
                            cl.Send();
                            }
                    default:
                        if(input > 0 && input <= ennemyDeck.getSize()){
                            if(!GB[4 * dim + 4].isOccupied()){
                                deployUnitEnnemy(input);
                            }
                            else cout << "La base est deja occupée, deployer une unite est impossible" << endl;
                        }
                        else {cout << "input non reconnu, svp ressayer" << endl;}
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
            else{ //PHASE DE BATAILLE
                cout << "unites disponibles: " << endl;
                for(auto i = ennemyUnits.begin(); i != ennemyUnits.end(); i++){
                    cout << y << ". ";
                    (*i).afficherConsole();
                    y++;
                }
                cout << "quelle carte voulez vous utiliser? - tapez 0 pour abandoner le jeu sinon le # de la carte" << endl;
                cin >> cl.buffer;
                input = (int)*cl.buffer-48;
                cl.Send();
                switch(input){
                    case 0:
                        stay = false;
                        break;
                    default:
                        cout <<"playerdeck size = "<< ennemyUnits.size() << endl;
                        if(input > 0 && (unsigned int)input <= ennemyUnits.size()){
                        while(actUnit){
                            cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
                            cin >> cl.buffer;
                            xmove = (int)*cl.buffer-48;
                            cl.Send();
                            cin >> cl.buffer;
                            ymove = (int)*cl.buffer-48;
                            cl.Send();
                            if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                                if(!GB.getTable()[ymove*dim+xmove].isOccupied()){ //Si case vide
                                        moveUnitEnnemy(input);
                                }
                                else {
                                    attackByEnnemy(input);
                                }
                            }
                            else {cout << "position non valide dans le tableau, svp reesayer" << endl;}
                        } 
                        }
                        else {cout << "input non reconnu, svp ressayer" << endl;}
                        actUnit = true;
                        GB.afficherConsole();
                        break;
                }
                y = 1;
            }
        }
    GB.afficherConsole();
    cl.Close();
}

