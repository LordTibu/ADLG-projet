PROJET LIFAP4 2022 - ADGL
Fait Par:
	-Nicolas Patino - P1926177
	-Juan C. Lenis - P1925046

Pre-requis pour la compilation (apart SDL):
	-Librerie SDL_Net (code source dans le dossier "include")
Pour compiler le projet (Linux) appeler la commande "make" depuis le fichier racine.

ADGL c'est un jeu de cartes 1 vs 1 où les jouers combatent avec leurs heros pour essayer de vaincre le champion ennemi.
Pendant un tour du jeu, le joueur peut faire des actions pendant deux phases du jeu,
- La phase de deploiement : Le joueur peut deploiyer une des cartes dans son deck dans le tableau.
- La phase de deplacement/combat : Le joueur peut déplacer un de ses heros ou l'utiliser pour attaquer un des heros ennemis.
Le Jeu est fini quand un des joueurs tue le Champion de l'adversaire.

Le jeu peut etre joué en local (deux personnes dans le meme ordinateur) ou en LAN, où un des joueurs host le serveur dans sa machine et l'adversaire se connecte avec le module client de l'appliclation.
Le jeu possede aussi une version texte et une version graphique faite à l'aide de SDL2.

Organisation des dossiers:
- Assets : C'est là où se trouvent tous les ressources necesaires pour le jeu (textures SDL, fichiers .txt avec les donnes des cartes, etc..).
- Bin : Plusieurs executables seront produits dans le dossier bin:
	1. bin/deckTest : Test du module deckBuilder qui permet à l'utilisateur de personnaliser son deck.
	2. bin/mainTest : Module qui contient les versions texte des differentes versions du jeu (en local ou en LAN).
	3. bin/main2D : Module qui contient la version SDL du jeu.
- Doc : La documentation du code.
- Include : Dossier contenant la librerie SDL_net.
- Obj : Dossier où sont organisés les differents .obj.
- Src : Fichiers .cpp et .h contenant le code de l'application.
