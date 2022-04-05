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

gameSquare::~gameSquare(){}

bool gameSquare::getOccupier() {return occupier;}

void gameSquare::occupy(const unit& u){
    occupier = true;
    unitName = u.getName();
}

void gameSquare::deOccupy(){
    occupier = false;
}

void gameSquare::setName(const std::string& s){
    unitName = s;
}

void gameSquare::afficherConsole(){
    if(!occupier) {std::cout << "###  ";}
    else {std::cout << unitName << "  ";}
}

