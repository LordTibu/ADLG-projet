#include "cardLib.h"
#include <bits/stdc++.h>
using namespace std;

cardLib::cardLib() {}
cardLib::~cardLib() {
    cout << "Carlib destroyed" << endl;
}

bool compCard(const card &c, const card& d){
    return (c.getName() < d.getName());
}


void cardLib::fillLibrary(const std::string & filename){
    ifstream fichier (filename.c_str());
    assert(fichier.is_open());
    unsigned int id, nhp, natk, nptr, nmov, natkr;
    string name, desc;
    while(fichier >> name >> desc >> id >> nhp >> natk >> nptr >> nmov >> natkr){
        cardLibrary.push_back(card(name, desc, id, nhp , natk, nptr, nmov, natkr));
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

void cardLib::sortD(){
    sort(cardLibrary.begin(), cardLibrary.end(), compCard);
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