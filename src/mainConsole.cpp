#include "gameBoard.h"
using namespace std;

int getIndex(int x, int y, vector<unit> v) {
    int u = -1;
    for(int i = 0; i < v.size(); i++) {
    if(v[i].getX() == x && v[i].getY() == y) {u = i;}
    }
    return u;
}

int main(void){
    unsigned int xmove, ymove;
    int input;
    bool stay = true;
    bool deployPhase = true;
    bool actUnit = true;
    bool playerTurn = true;
    unsigned int dim = 5;
    unit easeUnit; // ptr pour faire plus lisibles les operations
    gameBoard GB = gameBoard(dim, dim);
    cardLib defaultPieces;
    defaultPieces.fillLibrary("./assets/units.txt");
    vector<card>& lib = defaultPieces.getLib();
    vector<unit> playerDeck;
    vector<unit> playerUnits;
    vector<unit> ennemyDeck;
    vector<unit> ennemyUnits;
    for(int i = 0; i < defaultPieces.getSize(); i++){ //Creation des decks a partir des cartes dans la librerie
        playerDeck.push_back(unit(lib[i], playerTurn));
        ennemyDeck.push_back(unit(lib[i], !playerTurn));
    }

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
                            if(GB.getTable()[0].getOccupier() == NULL){
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
                            if(GB.getTable()[4 * dim + 4].getOccupier() == NULL){
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
    return 0;
}