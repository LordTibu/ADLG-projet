#include "gameConsole.h"
#include<vector>
using namespace std;

int getIndex(int x, int y, vector<unit> v) {
    int u = -1;
    for(int i = 0; i < v.size(); i++) {
    if(v[i].getX() == x && v[i].getY() == y) {u = i;}
    }
    return u;
}

gameConsole::gameConsole(){}
gameConsole::~gameConsole(){}

void gameConsole::gameInit(unsigned int xdim, unsigned int ydim){
    GB.init(5,5); //creation du tableau de jeu
    defaultPieces.fillLibrary("./assets/units.txt"); 
    lib = defaultPieces.getLib();
    cout << "Size of lib = " << defaultPieces.getSize() << endl;
    for(int i = 0; i < defaultPieces.getSize(); i++){ //Creation des decks a partir des cartes dans la librairie
        playerDeck.push_back(unit(lib[i], playerTurn));
        ennemyDeck.push_back(unit(lib[i], !playerTurn));
    }
    std::cout << "Creation des Decks et du tableau de Jeu fait" << std::endl;
    GB.afficherConsole();
}

void gameConsole::gameHandleEvents(){
    unsigned int y= 1;
    if(playerTurn){
        cout << "PLAYER 1 TURN" << endl;
        if(deployPhase){ // DEPLOYMENT PHASE (ESTA EN INGLES PQ NO SE COMO DECIRLO EN FRANCES)
            cout << "cartes disponibles: " << endl;
            for(auto i = playerDeck.begin(); i != playerDeck.end(); i++){
                cout << y << ". ";
                (*i).afficherConsole();
                y++;
            }
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
}

void gameConsole::gameUpdate(){
    unsigned int y = 1;
    GB.afficherConsole();
    while(stay){
        if(playerTurn){
            cout << "********************" << endl;
            cout << "PLAYER TURN" << endl;
            cout << "********************" << endl;
            cout << endl;
            if(deployPhase){ //DEPLOYMENT PHASE
                cout << "cartes disponibles: " << endl;
                for(int i = 0; i < playerDeck.size(); i++){
                    cout << y << ". ";
                    lib[i].afficherConsole();
                    y++;
                }
                cout <<"deck size = "<< playerDeck.size() << endl;
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
                        if(input > 0 && (unsigned int)input <= playerDeck.size()){
                            if(!GB.getTable()[0].getOccupier()){
                                playerUnits.push_back(playerDeck[input - 1]); // on insere la carte dans le tab d'unites
                                GB.getTable()[0].occupy(); // indique que la case est occupée (utile pour affichage console)
                                playerUnits.back().moveTo(0,0); // on initialise la position de l'unite
                                //vector<unit>::iterator it = playerDeck.begin();
                                playerDeck.erase(playerDeck.begin() + (input - 1)); // on elimine la carte du deck
                                deployPhase = !deployPhase;
                            }
                            else cout << "La base est deja occupée, deployer une unite est impossible" << endl;
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
                                if(!GB.getTable()[ymove*dim+xmove].getOccupier()){ //Si non occupé, on bouge
                                        easeUnit = playerUnits[input - 1]; // pour lisibilité
                                        GB.getTable()[easeUnit.getY() * dim + easeUnit.getX()].deOccupy(); //on libere la case anterieur
                                        playerUnits[input - 1].moveTo(xmove, ymove); // on bouge l'unite
                                        GB.getTable()[ymove * dim + xmove].occupy();
                                        actUnit = false;
                                        deployPhase = !deployPhase;
                                        playerTurn = !playerTurn;
                                }
                                else {
                                        int index = getIndex(xmove, ymove, playerUnits);
                                        if(index > 0) { // Si l'unite est une unite alliée
                                        cout << "position deja occupée par une autre unite, svp reesayer" << endl;
                                        }
                                        else{
                                            index = getIndex(xmove, ymove, ennemyUnits);
                                            cout << endl;
                                            cout << "********************" << endl;
                                            cout << "Initiating battle" << endl;
                                            cout << "********************" << endl;
                                            cout << endl;
                                            if(playerUnits[input - 1].battleUnit(ennemyUnits[index])){ // Si victoire alliée
                                                ennemyUnits.erase(ennemyUnits.begin() + index); // On elimine l'unite ennemie
                                                GB.getTable()[playerUnits[input - 1].getY() * dim + playerUnits[input - 1].getX()].deOccupy(); //on deOccupe la case anterieur
                                                playerUnits[input - 1].moveTo(xmove, ymove); // on update xpos et ypos l'unite
                                            }
                                            else{ // En cas de defaite
                                                GB.getTable()[playerUnits[input - 1].getY() * dim + playerUnits[input - 1].getX()].deOccupy();
                                                playerUnits.erase(std::next(playerUnits.begin(), input - 1));
                                            }
                                            actUnit = false;
                                            deployPhase = !deployPhase;
                                            playerTurn = !playerTurn;
                                        }
                                    
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
                for(auto i = ennemyDeck.begin(); i != ennemyDeck.end(); i++){
                    cout << y << ". ";
                    (*i).afficherConsole();
                    y++;
                }
                cout <<"deck size = "<< ennemyDeck.size() << endl;
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
                        if(input > 0 && (unsigned int)input <= ennemyDeck.size()){
                            if(!GB.getTable()[4 * dim + 4].getOccupier()){
                                ennemyUnits.push_back(ennemyDeck[input - 1]);
                                GB.getTable()[(dim-1)*dim+dim-1].occupy(); // insere la piece choisice dans le table de jeu
                                ennemyUnits.back().moveTo(dim-1,dim-1);
                                ennemyDeck.erase(std::next(ennemyDeck.begin(), input - 1));
                                deployPhase = !deployPhase;
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
                                if(!GB.getTable()[ymove*dim+xmove].getOccupier()){ //Si case vide
                                        easeUnit = ennemyUnits[input - 1]; // pour lisibilité
                                        GB.getTable()[easeUnit.getY() * dim + easeUnit.getX()].deOccupy(); //on deOccupe la case anterieur
                                        ennemyUnits[input - 1].moveTo(xmove, ymove); // on bouge l'unite
                                        GB.getTable()[ymove * dim + xmove].occupy();
                                        actUnit = false;
                                        deployPhase = !deployPhase;
                                        playerTurn = !playerTurn;
                                }
                                else {
                                        cout << "made it here" << endl;
                                        int index = getIndex(xmove, ymove, ennemyUnits);
                                        if(index > 0) { // Si l'unite est une unite alliée
                                        cout << "position deja occupée par une autre unite, svp reesayer" << endl;
                                        }
                                        else{
                                            index = getIndex(xmove, ymove, playerUnits);
                                            cout << "********************" << endl;
                                            cout << "Initiating battle" << endl;
                                            cout << "********************" << endl;
                                            if(ennemyUnits[input - 1].battleUnit(playerUnits[index])){ // Si victoire alliée
                                                playerUnits.erase(playerUnits.begin() + index); // On elimine l'unite ennemie
                                                GB.getTable()[ennemyUnits[input - 1].getY() * dim + ennemyUnits[input - 1].getX()].deOccupy(); //on deOccupe la case anterieur
                                                ennemyUnits[input - 1].moveTo(xmove, ymove); // on update xpos et ypos l'unite
                                            }
                                            else{ // En cas de defaite
                                                GB.getTable()[ennemyUnits[input - 1].getY() * dim + ennemyUnits[input - 1].getX()].deOccupy();
                                                ennemyUnits.erase(std::next(playerUnits.begin(), input - 1));
                                            }
                                            actUnit = false;
                                            deployPhase = !deployPhase;
                                            playerTurn = !playerTurn;
                                        }
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

bool gameConsole::Stay(){return stay;}