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
        userDeck.ajouterCarte(defLib.getLib()[input - 1]);
        cout << "La carte a été ajoutée a votre Deck" << endl;
        cout << "************************" << endl;
    }
    else{
        cout << "Input non reconnu, svp reessayer" << endl;
        cout << "************************" << endl;
    }
}

void deckBuilder::removeCard(){
    cout << "Quelle carte souhaitez vous supprimer?" << endl;
    userDeck.afficher();
    cin >> input;
    if(input > 0 && input <= defLib.getSize()){
        userDeck.supprimerCarte(input - 1);
        cout << "La carte a été supprime de votre Deck" << endl;
        cout << "************************" << endl;
    }
    else{
        cout << "Input non reconnu, svp reessayer" << endl;
        cout << "************************" << endl;
    }
}

void deckBuilder::sortDeck(){
    
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
        stay = false;
        if(!saved){
            cout << "Vous avez pas enregistré vos changements:" << endl;
            cout << "1. Sauvegarder et quitter" << endl;
            cout << "2. Quitter" << endl;
            cin >> input;
            if(input == 1) saveDeck();
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
    userDeck.saveToFile("./assets/userDeck.txt");
    cout << "Le Deck a été enregistré" << endl;
    cout << "************************" << endl;
}