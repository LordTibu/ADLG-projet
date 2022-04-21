#include "card.h"
using namespace std;

card::card(){
    name = description = "";
    index = life = attack = 0;
}

card::card(std::string Nname, std::string Ndesc, unsigned int Nindex, unsigned int Nlife, unsigned int Nattack, unsigned int Nprotection, 
           unsigned int nRange, unsigned int nAtkRange){
    name = Nname;
    description = Ndesc;
    index = Nindex;
    life = Nlife;
    attack = Nattack;
    protection = Nprotection;
    movRange = nRange;
    atkRange = nAtkRange;
}

card::~card(){}

void card::afficherConsole() const{
    cout << name << "(atk = " << attack << "; life = " << life <<"; ptr = " << protection << ")" << endl;
}

void card::afficherInitiales() const{
    assert(name != "");
    cout << name.at(0) << name.at(1);
}

string card::getName() const{
    return name;
}

ostream& operator<<(ostream& os, card c){
    os << c.name << " " << c.description << " " << c.index << " " << c.life << " " << c.attack << " " << c.protection;
    return os;
}