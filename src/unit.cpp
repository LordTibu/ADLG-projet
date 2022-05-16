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
    isChamp = Ncard.isChamp;
    canMove = true;
    canAttack = true;
    if(player1) {xpos = ypos = -1;}
    else {xpos = ypos = -1;}
    appliedStatus.push_back({-1 , -1});
}

unit::~unit(){
    cardIndex = NULL;
}

int unit::getX() const {return xpos;}
int unit::getY() const {return ypos;}
int unit::getAtkRange() const{
    return atkRange;
}
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
    int atk_m;
    if(ennemy.ptr >= atk){
        ennemy.ptr -= atk;
    }else { 
        atk_m = atk - ennemy.ptr;
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
    int atk_m;
    if(ennemy.ptr >= atk){
        ennemy.ptr -= atk;
    }else { 
        atk_m = atk - ennemy.ptr;
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
    attackUnit(ennemy);
    if(attackStatus.statIndex != -1){
    ennemy.addAppliedStatus(attackStatus);
    }
    if(ennemy.hp == 0){
        std::cout << "#### L'unite ennemie est eliminé ####" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        return true;
    }
    return false;
}

bool unit::battleUnitNET(unit &ennemy){
    attackUnitNET(ennemy);
    if(attackStatus.statIndex != -1){
    ennemy.addAppliedStatus(attackStatus);
    }
    if(ennemy.hp == 0){
        std::cout << "#### L'unite ennemie est eliminé ####" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        return true;
    }
    return false;
}

void unit::afficherConsole() const{
    std::cout << unitName << ": " << "current atk: " << atk << "; current hp: " << hp << "; current ptr: "<< ptr <<std::endl;
}

void unit::afficherInitiales(){
    std::cout << unitName.at(0) << unitName.at(1);
    if(player1) std::cout << "P "; //to identify as a Player or Ennemy unit
    else std::cout << "E ";
}

void unit::afficherPosition(){
    std::cout << "pos: " << xpos  << ";" << ypos << std::endl;
}

bool unit::moveTo(int x, int y){
    if(isInRange(x, y)){
    xpos = x;
    ypos = y;
    return true;
    }
    std::cout << "Position out of move range" << std::endl;
    return false;
}

void unit::applyStatus(const status& s){
    std::string name;
    name = s.getName();
    name.pop_back(); //name a \n a la fin du coup faut l'enlever
    if(name == "Poisoned"){
        std::cout << "applied Poisoned to unit" << std::endl;
        if(hp > 1) hp -= 1;
    }
    if((name == "Frozen")){
        std::cout << "applied Frozen to unit" << std::endl;
        canMove = false;
        canAttack = false;
    }
    if(name == "Blinded"){
         std::cout << "applied Blinded to unit" << std::endl;
        canAttack = false;
    }
    if(name == "Rooted"){
         std::cout << "applied Rooted to unit" << std::endl;
        canMove = false;
    }
    if(name == "Weakened"){
         std::cout << "applied Weakened to unit" << std::endl;
        if(atk > 1) atk -= 1;
    }
}

void unit::addAppliedStatus(const statusInfo& s){
    int i = 0;
    bool b = true;
    while(i < (int)appliedStatus.size() && b){
        if(appliedStatus[i].statIndex == s.statIndex){
            appliedStatus[i].statStrength += s.statStrength;
            b = false;
        }
        i++;
    }
    if(!b) appliedStatus.push_back(s);
}

int unit::getAppliedSize() const{
    return appliedStatus.size();
}
statusInfo& unit::getAppliedStatus(int index){
    return appliedStatus[index];
}
void unit::eraseAppliedStatus(int index){
    appliedStatus.erase(appliedStatus.begin() + index);
}

void unit::setTo(int x, int y){
    xpos = x;
    ypos = y;
}

bool unit::isInRange(int x, int y) const {
    return  abs(x - xpos) + abs( y - ypos) <= movRange;
}

bool unit::isInAtkRange(int x, int y) const {
    return abs(x - xpos) + abs(y - ypos) <= movRange + atkRange;
}

bool unit::itsChamp() const{
    return isChamp;
}

bool unit::operator==(const unit &u){
        return xpos==u.xpos && ypos==u.ypos;
    }