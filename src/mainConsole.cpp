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
    unsigned int dim = 5;
    unit* easeUnit; // ptr pour faire plus lisibles les operations
    gameBoard GB = gameBoard(dim, dim);
    cardLib defaultPieces;
    defaultPieces.fillLibrary();
    list<card>& lib = defaultPieces.getLib();
    list<unit> playerDeck;
    list<unit> playerUnits;
    for(auto i = lib.begin(); i != lib.end(); i++){
        (*i).afficherConsole();
        playerDeck.push_back(unit((*i), true));
    }
    unsigned int y = 1;
    GB.afficherConsole();
    while(stay){
        if(deployPhase){
            cout << "cartes disponibles: " << endl;
            for(auto i = playerDeck.begin(); i != playerDeck.end(); i++){
                cout << y << ". ";
                (*i).afficherConsole();
                y++;
            }
            cout << "quelle carte voulez vous jouer? - tapez 0 pour abandoner le jeu sinon le # de la carte, 100 pour passer" << endl;
            cin >> input;
            switch(input){
                case 0:
                    stay = false;
                    break;
                case 100:
                    deployPhase = !deployPhase; 
                    break;
                default:
                    if(input > 0 && (unsigned int)input <= playerDeck.size()){
                        playerUnits.push_back(*getUnit(input - 1, playerDeck));
                        GB.getTable()[0].occupy(&playerUnits.back()); // insere la piece choisice dans le table de jeu
                        playerUnits.back().moveTo(0,0);
                        playerDeck.erase(std::next(playerDeck.begin(), input - 1));
                        deployPhase = !deployPhase; 
                    }
                    else {cout << "input non reconnu, svp ressayer" << endl;}
                    GB.afficherConsole();
                    break;
            }
            y = 1;
        }
        else{
            cout << "unites disponibles: " << endl;
            for(auto i = playerUnits.begin(); i != playerUnits.end(); i++){
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
                    if(input > 0 && (unsigned int)input <= playerUnits.size()){
                       while(actUnit){
                           cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
                           cin >> xmove;
                           cin >> ymove;
                           if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                               if(GB.getTable()[ymove*dim+xmove].getOccupier() == NULL){
                                    easeUnit = getUnit(input - 1, playerUnits); // pour lisibilité
                                    GB.getTable()[easeUnit->getY() * dim + easeUnit->getX()].deOccupy(); //on deOccupe la case anterieur
                                    easeUnit->moveTo(xmove, ymove); // on bouge l'unite
                                    GB.getTable()[ymove * dim + xmove].occupy(easeUnit);
                                    actUnit = false;
                                    deployPhase = !deployPhase; 
                                }
                               else {cout << "position deja occupée par une autre unite, svp reesayer" << endl;}
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
    return 0;
}