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

unsigned int unit::getX() const {return xpos;}
unsigned int unit::getY() const {return ypos;}
bool unit::isPlayers() const {return player1;}

void unit::attackUnit(unit* ennemy){
    if(ennemy->hp <= atk) ennemy->hp = 0;
    else ennemy->hp -= atk;
    std::cout << unitName << " dealt " << atk << " dmg to " << ennemy->unitName << std::endl;
}

bool unit::battleUnit(unit* ennemy){
    bool turn = true;
    while(hp !=0 && ennemy->hp != 0){
        if(turn) attackUnit(ennemy);
        else ennemy->attackUnit(this);
        turn = !turn;
    }
    if(hp == 0){
        std::cout << "Mission Failed, we'll get them next time" << std::endl;
        return false;
    }
    else{
        std::cout << "Great Success, the Motherland shall be proud of your efforts" << std::endl;
        return true;
    }
}

void unit::afficherConsole() const{
    std::cout << cardIndex->name << ": " << "current atk: " <<atk << "; current hp: " << hp << std::endl;
}

void unit::afficherInitiales(){
    std::cout << unitName.at(0) << unitName.at(1);
    if(player1) std::cout << "P "; //to identify as a Player or Ennemy unit
    else std::cout << "E ";
}

void unit::afficherPosition(){
    std::cout << "pos: " << xpos  << ";" << ypos << std::endl;
}

void unit::moveTo(unsigned int x, unsigned int y){
    xpos = x;
    ypos = y;
}

bool unit::operator==(const unit &u){
        return xpos==u.xpos && ypos==u.ypos;
    }