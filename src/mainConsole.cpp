#include "gameBoard.h"
#include<vector>
using namespace std;

int main(void){
    unsigned int input, xmove, ymove;
    bool stay = true;
    bool deployPhase = true;
    bool actUnit = true;
    unsigned int dim = 5;
    gameBoard GB = gameBoard(dim, dim);
    cardLib defaultPieces;
    defaultPieces.fillLibrary();
    vector<card>& lib = defaultPieces.getLib();
    vector<unit> playerDeck;
    vector<unit> playerUnits;
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
            cout << "quelle carte voulez vous jouer? - tapez 0 pour abandoner le jeu sinon le # de la carte" << endl;
            cin >> input;
            switch(input){
                case 0:
                    stay = false;
                    break;
                default:
                    if(input > 0 && input <= playerDeck.size()){
                        cout << "input - 1 es: " << input - 1 << endl;
                        playerUnits.push_back(playerDeck.at(input - 1));
                        GB.getTable()[0].occupy(&playerUnits.back()); // insere la piece choisice dans le table de jeu
                        playerUnits.at(playerUnits.size() - 1).moveTo(0, 0);
                        playerUnits.at(playerUnits.size() - 1).afficherPosition();
                        GB.getTable()[0].getOccupier()->afficherConsole();
                        //playerDeck.erase(std::next(playerDeck.begin(), input - 1));
                    }
                    else {cout << "input non reconnu, svp ressayer" << endl;}
                    GB.afficherConsole();
                    break;
            }
            y = 1;
            deployPhase = !deployPhase; 
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
                    if(input > 0 && input <= playerUnits.size()){
                       while(actUnit){
                           cout << "a quelle case bouger l'unite? (donner x puis y en indice de tab)" << endl;
                           cin >> xmove;
                           cin >> ymove;
                           if(0 <= xmove && xmove < dim && 0 <= ymove && ymove < dim){
                               GB.getTable()[0*dim+0].deOccupy();
                               playerUnits[input - 1].moveTo(xmove, ymove);
                               GB.getTable()[ymove * dim + xmove].occupy(&playerUnits[input - 1]);
                               actUnit = false;
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
            deployPhase = !deployPhase;
        }
    }
    GB.afficherConsole();
    return 0;
}