#include "unit.h"

unit::unit(){
    cardIndex = NULL;
    atk = hp = 0;
}

unit::unit(card& Ncard, bool play){
    unitName = Ncard.name;
    cardIndex = &Ncard;
    hp = Ncard.life;
    atk = Ncard.attack;
    player1 = play;
    if(player1) {xpos = ypos = 99;}
    else {xpos = ypos = 4;}
}

unit::~unit(){}

void unit::attackUnit(unit* ennemy){
    ennemy->hp -= atk;
}

void unit::battleUnit(unit* ennemy){

}

void unit::afficherConsole() const{
    std::cout << cardIndex->name << ": " << "current atk: " <<atk << "; current hp: " << hp << std::endl;
}

void unit::afficherInitiales(){
    std::cout << unitName.at(0) << unitName.at(1);
}

void unit::afficherPosition(){
    std::cout << "pos: " << xpos  << ";" << ypos << std::endl;
}

void unit::moveTo(unsigned int x, unsigned int y){
    xpos = x;
    ypos = y;
}