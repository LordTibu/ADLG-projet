#ifndef DECKB_H
#define DECKB_H
#include"cardLib.h"

/*! \class deckBuilder
    \brief Application qui gere la creation et modification du Deck de l'user

    L'utilisateur dispose d'un Deck personalisé qu'il peut sauvergarder entre
    utilisations du jeu. C'est le deck avec lequel il bataille contre les autres joueurs
*/
class deckBuilder
{
private:
    int input; /** Input de l'utilisateur*/
    bool stay, /** Pour stopper l'application*/
        saved, /** Indique si le Deck de l'User a ete sauvegardé*/
        gotChamp; /** Indique si le Deck a un Champion (obligatoire)*/
    cardLib userDeck; /** Deck de l'utilisateur*/
    cardLib defLib; /** Deck qui contient toutes les cartes existantes du jeu (un codex)*/
public:
    deckBuilder();
    ~deckBuilder();
    bool Stay() const;
    /** Initialise l'application*/
    void init();
    /** Boucle pour updater l'application*/
    void run();
    /** Affiche l'application*/
    void afficher() const;
    /** Ajoute une carte au Deck de l'utilisateur*/
    void addCard(); 
    /** Enleve une carte du Deck de l'utilisateur*/
    void removeCard();
    /** Trie le Deck en ordre alphabetique (selon les noms des cartes)*/
    void sortDeck();
    /** Met a jour le fichier qui contient le Deck (userDeck.txt), si le Deck est valide,
     * avec les cartes actuellement dedans userDeck
    */
    void saveDeck(); 
    void setStay(bool s);
};
#endif
