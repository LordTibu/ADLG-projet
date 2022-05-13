#include"deckBuilder.h"
using namespace std;

deckBuilder::deckBuilder(){}
deckBuilder::~deckBuilder(){}

bool deckBuilder::Stay() const { return stay; }

void deckBuilder::init(){
    saved = true;
    stay = true;
    defLib.fillLibrary("./assets/units.txt");
    userDeck.fillLibrary("./assets/userDeck.txt");
    gotChamp = userDeck.hasChamp();
}

void deckBuilder::afficher() const {
    cout << "Cartes disponibles: " << endl;
    defLib.afficher();
    cout << "Cartes dans le Deck: " << endl;
    userDeck.afficher();
    cout << "************************" << endl;
}

void deckBuilder::addCard(){
    cout << "Quelle carte souhaitez vous ajouter?" << endl;
    defLib.afficher();
    cin >> input;
    if(input > 0 && input <= defLib.getSize()){
        if(defLib[input - 1].itsChamp()){
            if(gotChamp){ //Si il y a deja un champ. dans le userDeck
                cout << "Vous avez deja un champion dans votre deck, supprimer le precedent avant d'ajouter un nouveau" << endl;
                cout << "************************" << endl;
            }
            else{
                gotChamp = true;
                userDeck.ajouterCarte(defLib[input - 1]);
                cout << "La carte a été ajoutée a votre Deck" << endl;
                cout << "************************" << endl;
                saved = false;
            }
        }
    }
    else{
        cout << "Input non reconnu, svp reessayer" << endl;
        cout << "************************" << endl;
    }
    sortDeck();
}

void deckBuilder::removeCard(){
    cout << "Quelle carte souhaitez vous supprimer?" << endl;
    userDeck.afficher();
    cin >> input;
    if(input > 0 && input <= defLib.getSize()){
        if(userDeck[input - 1].itsChamp()) gotChamp = false;
        userDeck.supprimerCarte(input - 1);
        cout << "La carte a été supprime de votre Deck" << endl;
        cout << "************************" << endl;
    }
    else{
        cout << "Input non reconnu, svp reessayer" << endl;
        cout << "************************" << endl;
        saved = false;
    }
}

void deckBuilder::sortDeck(){
    userDeck.sortD();
}

void deckBuilder::run(){
    afficher();
    cout << "Choisir une action: " << endl;
    cout << "1. Ajouter une Carte dans votre Deck" << endl;
    cout << "2. Supprimer une carte de votre Deck" << endl;
    cout << "3. Sauvegarder votre Deck" << endl;
    cout << "0. Fermer le manager de Deck" << endl;
    cout << "(Tapez le numero en indice pour choiser votre action)" << endl;
    cin >> input;
    switch (input)
    {
    case 0:
        if(gotChamp){
            stay = false;
            if(!saved){
                cout << "Vous avez pas enregistré vos changements:" << endl;
                cout << "1. Sauvegarder et quitter" << endl;
                cout << "2. Quitter" << endl;
                cin >> input;
                if(input == 1) saveDeck();
            }
        }
        else{
            cout << "Vous n'avez pas de champion dans votre deck, vos changements ne seront pas sauvegardés" << endl;
            cout << "Quitter tout de meme?" << endl;
            cout << "1. Revenir en arriere" << endl;
            cout << "2. Quitter" << endl;
            cin >> input;
            if(input == 2) stay = false;
        }
        break;
    case 1:
        addCard();
        break;
    case 2:
        removeCard();
        break;
    case 3:
        saveDeck();
        break;
    default:
        cout << "input non reconnu, svp ressayer" << endl;
        break;
    }
}

void deckBuilder::saveDeck(){
    if(userDeck.hasChamp()){
        userDeck.saveToFile("./assets/userDeck.txt");
        cout << "Le Deck a été enregistré" << endl;
        cout << "************************" << endl;
    }
    else{
        cout << "Vous ne pouvez pas enregistrer un deck sans champion" << endl;
    }
}