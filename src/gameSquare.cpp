#include "gameSquare.h"

gameSquare::gameSquare(){
    occupied = false;
    terrain = "0";
}

gameSquare::gameSquare(std::string terra, bool occupy){
    occupied = occupy;
    terrain = terra;
}

gameSquare::~gameSquare(){}

bool gameSquare::isOccupied() const {return occupied;}

void gameSquare::occupy(const unit& u){
    occupied = true;
    unitName = u.getName();
}

void gameSquare::deOccupy(){
    occupied = false;
}

void gameSquare::setName(const std::string& s){
    unitName = s;
}

void gameSquare::afficherConsole(){
    if(!occupied) {std::cout << "###  ";}
    else {std::cout << unitName << "  ";}
}

