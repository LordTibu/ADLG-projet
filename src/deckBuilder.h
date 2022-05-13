#ifndef DECKB_H
#define DECKB_H
#include"cardLib.h"

class deckBuilder
{
private:
    int input;
    bool stay, saved, gotChamp;
    cardLib userDeck;
    cardLib defLib; //default library, to house all cards
public:
    deckBuilder();
    ~deckBuilder();
    bool Stay() const;
    void init();
    void run();
    void afficher() const;
    void addCard(); //ajouter carte au deck
    void removeCard(); // enlever carte du deck
    void sortDeck(); // mettre en  ordre (alphabetique) les cartes du deck
    void saveDeck(); // mettre a jour userDeck.txt avec les cartes dedans userDeck
};
#endif
