#include "card.h"
using namespace std;

card::card(){
    name = description = "";
    index = life = attack = 0;
}

card::card(std::string Nname, std::string Ndesc, unsigned int Nindex, unsigned int Nlife, unsigned int Nattack, unsigned int Nprotection){
    name = Nname;
    description = Ndesc;
    index = Nindex;
    life = Nlife;
    attack = Nattack;
    protection = Nprotection;
}

card::~card(){}

void card::afficherConsole() const{
    cout << name << "(atk = " << attack << "; life = " << life <<"; ptr = " << protection << ")" << endl;
}

void card::afficherInitiales() const{
    assert(name != "");
    cout << name.at(0) << name.at(1);
}