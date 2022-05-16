#include"statusCodex.h"
#include <sstream>
using namespace std;

statusCodex::statusCodex(){}
statusCodex::~statusCodex(){}

void statusCodex::init(const string& filename){
    ifstream fichier (filename.c_str());
    assert(fichier.is_open());
    string name, description, s;
    while(getline(fichier, name)){
        getline(fichier, description, '/');
        getline(fichier, s); //Pour enlever le '\n' apres la description
        codex.push_back(status(name, description));
    }
}

void statusCodex::afficher() const{
    for(int i = 0; i < (int)codex.size(); i++){
        cout << codex[i];
    }
}

status& statusCodex::operator[](int index){
    return codex[index];
}