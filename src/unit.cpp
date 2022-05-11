#include "unit.h"
#include <chrono>
#include <thread>

unit::unit(){
    cardIndex = NULL;
    atk = hp = 0;
}

unit::unit(card& Ncard, bool play){
    unitName = Ncard.name;
    cardIndex = &Ncard;
    hp = Ncard.life;
    atk = Ncard.attack;
    ptr = Ncard.protection;
    player1 = play;
    movRange = Ncard.movRange;
    atkRange = Ncard.atkRange;
    if(player1) {xpos = ypos = -1;}
    else {xpos = ypos = -1;}
}

unit::~unit(){
    cardIndex = NULL;
}

unsigned int unit::getX() const {return xpos;}
unsigned int unit::getY() const {return ypos;}
std::string unit::getName() const {
    std::string r;
    r.push_back(unitName.at(0));
    r.push_back(unitName.at(1));
    if(player1) r.push_back('P');
    else r.push_back('E');
    return r;}
bool unit::isPlayers() const {return player1;}

void unit::attackUnit(unit &ennemy){
    if(isInAtkRange(ennemy.xpos, ennemy.ypos)){
    unsigned int atk_m;
    if(ennemy.ptr >= atk){
        ennemy.ptr -= atk;
    }else { 
        atk_m= atk - ennemy.ptr;
        if(ennemy.hp <= atk_m){
            ennemy.ptr = 0;
            ennemy.hp = 0;
        } else {
            ennemy.ptr = 0;
            ennemy.hp -= atk_m;
        }
    }
    if(player1){
        std::cout <<"@PLAYER : "<< unitName << " dealt " << atk << " dmg to @ENNEMY : " << ennemy.unitName << std::endl;
        std::cout <<"#####@ENNEMY current stats : " << ennemy.unitName << " hp = " << ennemy.hp << " ptr = "<< ennemy .ptr << std::endl;
    } else{
        std::cout <<"@ENNEMY : "<< unitName << " dealt " << atk << " dmg to @PLAYER : " << ennemy.unitName << std::endl;
        std::cout <<"#####@PLAYER current stats : " << ennemy.unitName << " hp = " << ennemy.hp << " ptr = "<< ennemy.ptr << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
    else{
        std::cout << "Ennemy outside of attack range" << std::endl;
    }
}

void unit::attackUnitNET(unit &ennemy){
    unsigned int atk_m;
    if(ennemy.ptr >= atk){
        ennemy.ptr -= atk;
    }else { 
        atk_m= atk - ennemy.ptr;
        if(ennemy.hp <= atk_m){
            ennemy.ptr = 0;
            ennemy.hp = 0;
        } else {
            ennemy.ptr = 0;
            ennemy.hp -= atk_m;
        }
    }
    if(player1){
        std::cout <<"@PLAYER 1: "<< unitName << " dealt " << atk << " dmg to @ENNEMY : " << ennemy.unitName << std::endl;
        std::cout <<"#####@PLAYER 2 current stats : " << ennemy.unitName << " hp = " << ennemy.hp << " ptr = "<< ennemy .ptr << std::endl;
    } else{
        std::cout <<"@pLAYER 2 : "<< unitName << " dealt " << atk << " dmg to @PLAYER : " << ennemy.unitName << std::endl;
        std::cout <<"#####@PLAYER 1 current stats : " << ennemy.unitName << " hp = " << ennemy.hp << " ptr = "<< ennemy.ptr << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

bool unit::battleUnit(unit &ennemy){
    bool turn = true;
    while(hp !=0 && ennemy.hp != 0){
        if(turn) attackUnit(ennemy);
        else ennemy.attackUnit(*this);
        turn = !turn;
    }
    if(hp == 0){
        std::cout << "Mission Failed, we'll get them next time" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        return false;
    }
    else{
        std::cout << "Great Success, the Motherland shall be proud of your efforts" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        return true;
    }
    
}

bool unit::battleUnitNET(unit &ennemy){
    bool turn = true;
    while(hp !=0 && ennemy.hp != 0){
        if(turn) attackUnitNET(ennemy);
        else ennemy.attackUnitNET(*this);
        turn = !turn;
    }
    if(hp == 0){
        std::cout << "Mission Failed, we'll get them next time" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        return false;
    }
    else{
        std::cout << "Great Success, the Motherland shall be proud of your efforts" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        return true;
    }
    
}

void unit::afficherConsole() const{
    std::cout << cardIndex->name << ": " << "current atk: " <<atk << "; current hp: " << hp << "; current ptr: "<<ptr <<std::endl;
}

void unit::afficherInitiales(){
    std::cout << unitName.at(0) << unitName.at(1);
    if(player1) std::cout << "P "; //to identify as a Player or Ennemy unit
    else std::cout << "E ";
}

void unit::afficherPosition(){
    std::cout << "pos: " << xpos  << ";" << ypos << std::endl;
}

bool unit::moveTo(unsigned int x, unsigned int y){
    if(isInRange(x, y)){
    xpos = x;
    ypos = y;
    return true;
    }
    std::cout << "Position out of move range" << std::endl;
    return false;
}

bool unit::isInRange(unsigned int x, unsigned int y) const {
    return x - xpos + y - ypos <= movRange;
}

bool unit::isInAtkRange(unsigned int x, unsigned int y) const {
    return x - xpos + y - ypos <= movRange + atkRange;
}

bool unit::operator==(const unit &u){
        return xpos==u.xpos && ypos==u.ypos;
    }