#include<iostream>
#include<fstream>
#include<assert.h>
using namespace std;

int main(void){
    /*ifstream fichier ("assets/statusCodex.txt");
    assert(fichier.is_open());
    enum status{Poisoned, Regenerating, Normal, Frozen};
    string alabama, jesus, norm, n;
    std::getline(fichier, alabama);
    std::getline(fichier, jesus, '/');
    std::getline(fichier, n);
    std::getline(fichier, norm);
    //fichier >> norm;
    status stat;
    cout << alabama << endl;
    cout << jesus << endl;
    cout << norm << endl;*/
    string s = "Platano";
    if(s == "Platano") cout << "si funciona" << endl;
    return 0;
}