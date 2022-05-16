#ifndef GAMECONSOLE_H
#define GAMECONSOLE_H

#include"gameBoard.h"
#include"server.h"
#include"client.h"

/*! \class gameConsole
    \brief Classe qui gère le jeu en version console

    Cette application permet de jouer une partie du jeu en local
    ou en connexion LAN en version Console
*/
class gameConsole
{
private:
    unsigned int xmove, /** input de l'utilisateur pour bouger une unit*/
    ymove; /** input de l'utilisateur pour bouger une unit*/
    int input; /** input de l'utilisateur pour controler plusieurs aspects du jeu (comme quelle unite utiliser)*/ 
    bool stay = true; /** Boolean pour rester dans l'application*/
    bool deployPhase = true; /** Boolean pour savoir dans quelle "phase" du jeu on se trouve (deploiement/combat)*/
    bool actUnit = true; /** Boolean qui indique si le joueur a joue son tour*/
    bool playerTurn = true; /** Boolean qui indique quel joueur doit jouer*/
    unsigned int dim = 5; /** Dimension du tableau de jeu*/
    /** Vector qui contient tous les effets d'etat possibles
     * qui peuvent soufrir les units du jeu (Poisoned, Frozen, Weakened etc...) */
    statusCodex sCodex;
    std::string tableLine; /** String utilisée pour afficher une ligne du tableau de jeu en version console*/
    unit easeUnit; /** Unite utilise pour condenser un peu le code*/
    gameBoard GB; /** Tableu de jeu*/
    cardLib defaultPieces; /** Codex contenant toutes les Cartes existantes*/
    cardLib playerDeck; /** Deck qui contient les cartes du joueur 1*/
    std::vector<unit> playerUnits; /**Vector qui contient les unit du joueur 1*/
    cardLib ennemyDeck; /** Deck qui contient les cartes du joueur 2*/
    std::vector<unit> ennemyUnits; /**Vector qui contient les unit du joueur 2*/
    server sv;
    client cl;
    friend class game2D;
public:
    gameConsole();
    ~gameConsole();
    bool getdeployphase() const;
    /** Initialise le Jeu en version locale*/
    void gameInit(unsigned int xdim, unsigned int ydim);
    /** Initialise la partie Server du Jeu en version LAN*/
    void gameInitServer(unsigned int xdim, unsigned int ydim);
    /** Initialise la partie Client (qui va se connecter au server) du Jeu en version LAN*/
    void gameInitClient(unsigned int xdim, unsigned int ydim, char *arg1, int arg2);
    /** Boucle principale du Jeu en version locale et en affichage texte*/
    void gameUpdate();
    /** Boucle principale de la partie Server du Jeu en version LAN et en affichage texte*/
    void gameUpdateNET();
    /** Boucle principale de la partie Client du Jeu en version LAN et en affichage texte*/
    void gameUpdateNETClient();
    /**Boucle principale du Jeu en version locale et en affichage texte SDL*/
    void gameUpdateNO();
    /** Boucle principale de la partie Server du Jeu en version LAN et en affichage SDL*/
    void gameUpdateNETNO();
    /** Boucle principale de la partie Client du Jeu en version LAN et en affichage SDL*/
    void gameUpdateNETClientNO();
    /** Affiche le jeu en mode texte*/
    void gameAfficher();
    /** On n'utilise pas cette fonction mais on a peur de l'effacer et puis en avoir besoin*/
    void gameHandleEvents();
    //void gameEnd();
    /** Fonction charge de deploiyer une unit depuis le deck du joueur 1
     * @param input int choisi par l'utilisateur qui indique l'index de l'unit à deploiyer
    */
    void deployUnitPlayer(int input);
    /** Fonction charge de deploiyer une unit depuis le deck du joueur 2
     * @param input int choisi par l'utilisateur qui indique l'index de l'unit à deploiyer
    */
    void deployUnitEnnemy(int input);
    /** Fonction charge de bouger une unit du vector<unit> du joueur 1
     * @param input int choisi par l'utilisateur qui indique l'index de l'unit à bouger
    */
    void moveUnitPlayer(int input);
    /** Fonction charge de bouger une unit du vector<unit> du joueur 2
     * @param input int choisi par l'utilisateur qui indique l'index de l'unit à bouger
    */
    void moveUnitEnnemy(int input);
    /** Fonction charge de realiser un combat d'units debuté par le joueur 1
     * @param input int choisi par l'utilisateur qui indique l'index de l'unit qui va attaquer
    */
    void attackByPlayer(int input);
    /** Fonction charge de realiser un combat d'units debuté par le joueur 2
     * @param input int choisi par l'utilisateur qui indique l'index de l'unit qui va attaquer
    */
    void attackByEnnemy(int input);
    /** Fonction charge MaJ les effets d'etat des unit du joueur 1*/
    void updateStatusPlayer();
    /** Fonction charge MaJ les effets d'etat des unit du joueur 2*/
    void updateStatusEnnemy();
    /** Fonction qui verifie si une des conditions de fin de jeu est remplie*/
    void checkForGameEnd();
    /** Declenche une victorie dependant du joueur qui a gagne*/
    void triggerVictory(bool player);
    void triggerDraw();
    bool Stay();
};
#endif