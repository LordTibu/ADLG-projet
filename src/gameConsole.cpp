#include "gameConsole.h"
using namespace std;

unit* getUnit(unsigned int n, list<unit>& l){
    auto it = l.begin();
    for(unsigned int i = 0; i < n; i++) it++;
    return &*it;
}

gameConsole::gameConsole(){}
gameConsole::~gameConsole(){}

void gameConsole::gameInit(unsigned int xdim, unsigned int ydim){
    GB = gameBoard(xdim, ydim); //creation du tableau de jeu
    defaultPieces.fillLibrary(); 
    std::list<card>& lib = defaultPieces.getLib();
    for(auto i = lib.begin(); i != lib.end(); i++){ //Creation des decks a partir des cartes dans la librerie
        (*i).afficherConsole();
        playerDeck.push_back(unit((*i), playerTurn));
        ennemyDeck.push_back(unit((*i), !playerTurn));
    }
    std::cout << "Creation des Decks et du tableau de Jeu fait" << std::endl;
    GB.afficherConsole();
}

void gameConsole::gameHandleEvents(){
    unsigned int y = 1;
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
    if(playerTurn){
        if(deployPhase){
            switch(input){
                case 0:
                    stay = false;
                    break;
                case 100:
                    deployPhase = !deployPhase; 
                    break;
                default:
                    if((unsigned int)input <= playerDeck.size()){
                        if(GB.getTable()[0].getOccupier() == NULL){
                            playerUnits.push_back(*getUnit(input - 1, playerDeck));
                            GB.getTable()[0].occupy(&playerUnits.back()); // insere la piece choisice dans le table de jeu
                            playerUnits.back().moveTo(0,0);
                            playerDeck.erase(std::next(playerDeck.begin(), input - 1));
                            deployPhase = !deployPhase;
                        }
                        else cout << "La base est deja occupée, deployer une unite est impossible" << endl;
                    }
                    else {cout << "input non reconnu, svp ressayer" << endl;}
                    GB.afficherConsole();
                    break;
            }
        }
        else{
             switch(input){
                case 0:
                    stay = false;
                    break;
                default:
                    if((unsigned int)input <= playerUnits.size()){
                        while(actUnit){
                            cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
                            cin >> xmove;
                            cin >> ymove;
                            if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                                if(GB.getTable()[ymove*dim+xmove].getOccupier() == NULL){ //Si non occupé, on bouge
                                        easeUnit = getUnit(input - 1, playerUnits); // pour lisibilité
                                        GB.getTable()[easeUnit->getY() * dim + easeUnit->getX()].deOccupy(); //on deOccupe la case anterieur
                                        easeUnit->moveTo(xmove, ymove); // on bouge l'unite
                                        GB.getTable()[ymove * dim + xmove].occupy(easeUnit);
                                        actUnit = false;
                                        deployPhase = !deployPhase;
                                        playerTurn = !playerTurn;
                                }
                                else {
                                    if(GB.getTable()[ymove*dim+xmove].getOccupier()->isPlayers()){ // Si unite allie occupe case
                                        cout << "position deja occupée par une autre unite, svp reesayer" << endl;
                                    }
                                    else{
                                        cout << "Initiating battle" << endl;
                                        if(getUnit(input - 1, ennemyUnits)->battleUnit(GB.getTable()[ymove*dim+xmove].getOccupier())){
                                            ennemyUnits.remove(*GB.getTable()[ymove*dim+xmove].getOccupier());
                                            GB.getTable()[ymove*dim+xmove].deOccupy();
                                            easeUnit = getUnit(input - 1, ennemyUnits); // pour lisibilité
                                            GB.getTable()[easeUnit->getY() * dim + easeUnit->getX()].deOccupy(); //on deOccupe la case anterieur
                                            easeUnit->moveTo(xmove, ymove); // on update xpos et ypos l'unite
                                            GB.getTable()[ymove * dim + xmove].occupy(easeUnit);
                                        }
                                        else{
                                            easeUnit = getUnit(input - 1, playerUnits); // pour lisibilité
                                            GB.getTable()[easeUnit->getY() * dim + easeUnit->getX()].deOccupy();
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
        }
    }
    else{
        if(deployPhase){
            switch(input){
                case 0:
                    stay = false;
                    break;
                case 100:
                    deployPhase = !deployPhase; 
                    break;
                default:
                    if((unsigned int)input <= ennemyDeck.size()){
                        if(GB.getTable()[0].getOccupier() == NULL){
                            playerUnits.push_back(*getUnit(input - 1, ennemyDeck));
                            GB.getTable()[0].occupy(&ennemyUnits.back()); // insere la piece choisice dans le table de jeu
                            playerUnits.back().moveTo(0,0);
                            playerDeck.erase(std::next(ennemyDeck.begin(), input - 1));
                            deployPhase = !deployPhase;
                        }
                        else cout << "La base est deja occupée, deployer une unite est impossible" << endl;
                    }
                    else {cout << "input non reconnu, svp ressayer" << endl;}
                    GB.afficherConsole();
                    break;
            }
        }
        else{
            switch(input){
                case 0:
                    stay = false;
                    break;
                default:
                    if(input > 0 && (unsigned int)input <= ennemyUnits.size()){
                        while(actUnit){
                            cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
                            cin >> xmove;
                            cin >> ymove;
                            if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                                if(GB.getTable()[ymove*dim+xmove].getOccupier() == NULL){
                                        easeUnit = getUnit(input - 1, ennemyUnits); // pour lisibilité
                                        GB.getTable()[easeUnit->getY() * dim + easeUnit->getX()].deOccupy(); //on deOccupe la case anterieur
                                        easeUnit->moveTo(xmove, ymove); // on bouge l'unite
                                        GB.getTable()[ymove * dim + xmove].occupy(easeUnit);
                                        actUnit = false;
                                        deployPhase = !deployPhase;
                                        playerTurn = !playerTurn;
                                }
                                else {
                                    if(!GB.getTable()[ymove*dim+xmove].getOccupier()->isPlayers()){ // Si unite allie occupe case
                                        cout << "position deja occupée par une autre unite, svp reesayer" << endl;
                                    }
                                    else{
                                        cout << "Initiating battle" << endl;
                                        if(getUnit(input - 1, ennemyUnits)->battleUnit(GB.getTable()[ymove*dim+xmove].getOccupier())){
                                            playerUnits.remove(*GB.getTable()[ymove*dim+xmove].getOccupier());
                                            GB.getTable()[ymove*dim+xmove].deOccupy();
                                            easeUnit = getUnit(input - 1, ennemyUnits); // pour lisibilité
                                            GB.getTable()[easeUnit->getY() * dim + easeUnit->getX()].deOccupy(); //on deOccupe la case anterieur
                                            easeUnit->moveTo(xmove, ymove); // on update xpos et ypos l'unite
                                            GB.getTable()[ymove * dim + xmove].occupy(easeUnit);
                                        }
                                        else{
                                            easeUnit = getUnit(input - 1, ennemyUnits); // pour lisibilité
                                            GB.getTable()[easeUnit->getY() * dim + easeUnit->getX()].deOccupy();
                                            ennemyUnits.erase(std::next(ennemyUnits.begin(), input - 1));
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
                
        }
    }
}

bool gameConsole::Stay(){return stay;}