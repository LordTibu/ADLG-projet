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
    string name, desc;
    while(fichier >> name >> desc >> id >> nhp >> natk >> nptr){
        cardLibrary.push_back(card(name, desc, id, nhp , natk, nptr));
    }
    fichier.close();
}

void cardLib::saveToFile(const std::string & filename){
    ofstream fichier (filename.c_str());
    assert(fichier.is_open());
    for(unsigned int i = 0; i < cardLibrary.size(); i++){
        fichier << cardLibrary[i] << endl;
    }
    fichier.close();
}

void cardLib::afficher() const {
    for(int i = 0; i < cardLibrary.size(); i++){
        cout << i + 1 <<". ";
        cardLibrary[i].afficherConsole();
    }
}

void cardLib::ajouterCarte(const card &c){
    cardLibrary.push_back(c);
}

void cardLib::supprimerCarte(int index){
    cardLibrary.erase(cardLibrary.begin()+index);
}

std::vector<card>& cardLib::getLib(){
    return cardLibrary;
}

int cardLib::getSize() const {return cardLibrary.size();}