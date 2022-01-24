#include "gameSquare.h"

gameSquare::gameSquare(){
    occupier = NULL;
    building = NULL;
    terrain = "";
}

gameSquare::gameSquare(std::string terra, unit* occupy, unit* build){
    occupier = occupy;
    building = build;
    terrain = terra;
}

gameSquare::~gameSquare(){

}

unit* gameSquare::getOccupier() {return occupier;}

void gameSquare::occupy(unit* Noccupier){
    occupier = Noccupier;
}

void gameSquare::deOccupy(){
    occupier = NULL;
}

void gameSquare::afficherConsole() const{
    if(occupier == NULL) {std::cout << "# ";}
    else {occupier->afficherInitiales();}
}

