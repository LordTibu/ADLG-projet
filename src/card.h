#include<string>
#include<iostream>

class card
{
private:
    std::string name, description;
    unsigned int index, life, attack;
    friend class unit; // Les unites ont access aux données des cartes pour utiliser ses stats
public:
    card();
    card(std::string nom, std::string Ndesc, unsigned int Nindex, unsigned int Nlife, unsigned int Nattack);
    ~card();
    void afficherConsole();
};
