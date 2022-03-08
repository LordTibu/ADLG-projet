#include "gameBoard.h"
#include<vector>
using namespace std;

unit* getUnit(unsigned int n, list<unit>& l){
    auto it = l.begin();
    for(unsigned int i = 0; i < n; i++) it++;
    return &*it;
}

int main(void){
    unsigned int xmove, ymove;
    int input;
    bool stay = true;
    bool deployPhase = true;
    bool actUnit = true;
    bool playerTurn = true;
    unsigned int dim = 5;
    unit* easeUnit; // ptr pour faire plus lisibles les operations
    gameBoard GB = gameBoard(dim, dim);
    cardLib defaultPieces;
    defaultPieces.fillLibrary("./assets/units.txt");
    list<card>& lib = defaultPieces.getLib();
    list<unit> playerDeck;
    list<unit> playerUnits;
    list<unit> ennemyDeck;
    list<unit> ennemyUnits;
    for(auto i = lib.begin(); i != lib.end(); i++){ //Creation des decks a partir des cartes dans la librerie
        playerDeck.push_back(unit((*i), playerTurn));
        ennemyDeck.push_back(unit((*i), !playerTurn));
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
                for(auto i = playerDeck.begin(); i != playerDeck.end(); i++){
                    cout << y << ". ";
                    (*i).afficherConsole();
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
                            break;
                        } else { 
                            cout << "vous avez aucune carte dans votre deck, vous pouvez pas passer, quelle carte voulez vous jouer? " << endl;
                            cin >> input;
                            }
                    default:
                        if(input > 0 && (unsigned int)input <= playerDeck.size()){
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
                                if(GB.getTable()[ymove*dim+xmove].getOccupier() == NULL){ //Si non occupé, on bouge
                                        easeUnit = getUnit(input - 1, playerUnits); // pour lisibilité
                                        GB.getTable()[easeUnit->getY() * dim + easeUnit->getX()].deOccupy(); //on libere la case anterieur
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
                                        cout << endl;
                                        cout << "********************" << endl;
                                        cout << "Initiating battle" << endl;
                                        cout << "********************" << endl;
                                        cout << endl;
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
                                ennemyUnits.push_back(*getUnit(input - 1, ennemyDeck));
                                GB.getTable()[(dim-1)*dim+dim-1].occupy(&ennemyUnits.back()); // insere la piece choisice dans le table de jeu
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
                                        cout << "********************" << endl;
                                        cout << "Initiating battle" << endl;
                                        cout << "********************" << endl;
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
                y = 1;
            }
        }
    }
    GB.afficherConsole();
    return 0;
}