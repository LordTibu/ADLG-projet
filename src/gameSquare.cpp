#include "gameSquare.h"

gameSquare::gameSquare(){
    occupier = false;
    building = false;
    terrain = "0";
}

gameSquare::gameSquare(std::string terra, bool occupy, bool build){
    occupier = occupy;
    building = build;
    terrain = terra;
}

gameSquare::~gameSquare(){
    std::cout << "GameSquare destroyed" << std::endl;
}

bool gameSquare::getOccupier() {return occupier;}

void gameSquare::occupy(){
    occupier = true;
}

void gameSquare::deOccupy(){
    occupier = false;
}

void gameSquare::afficherConsole(){
    if(!occupier) {std::cout << "#   ";}
}

