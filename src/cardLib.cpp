#include "cardLib.h"
using namespace std;

cardLib::cardLib() {}
cardLib::~cardLib() {
    cout << "Carlib destroyed" << endl;
}


void cardLib::fillLibrary(const std::string & filename){
    ifstream fichier (filename.c_str());
    assert(fichier.is_open());
    unsigned int id, nhp, natk, nptr;
    string mot1, mot2;
    while(fichier >> mot1 >> mot2 >> id >> nhp >> natk >> nptr){
        cardLibrary.push_back(card(mot1, mot2, id, nhp , natk, nptr));
    }
    fichier.close();
}

std::vector<card>& cardLib::getLib(){
    return cardLibrary;
}

int cardLib::getSize() const {return cardLibrary.size();}