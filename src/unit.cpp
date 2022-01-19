#include "unit.h"

unit::unit(){
    cardIndex = NULL;
    atk = hp = 0;
}

unit::unit(card* Ncard, bool play){
    cardIndex = Ncard;
    hp = Ncard->life;
    atk = Ncard->attack;
    player1 = play;
}

unit::~unit(){}

void unit::attackUnit(unit* ennemy){
    ennemy->hp -= atk;
}

void unit::battleUnit(unit* ennemy){

}