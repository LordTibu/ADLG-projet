# LIFAP4 2022 PROJECT - ADGL

### Execution

```
$ git clone https://github.com/LordTibu/Gyromite-projet.git
$ make
$ ./bin/main2D
```

## Pre-requisites for compilation (apart SDL):
   ```
  SDL_Net library (source code in "include" folder)
   ```
## Game description

ADGL is a 1 vs 1 card game where players battle with their heroes to try and defeat the enemy's champion.
During a game turn, the player can take actions during two phases of the game,
- Deployment phase: The player can deploy one of the cards in his deck in the tableau.
- The move/combat phase: The player can move one of his heroes or use it to attack one of the enemy heroes.
The game is over when one of the players kills the opponent's Champion.

The game can be played locally (two people in the same computer) or in LAN, where one player hosts the server on his machine and the opponent connects with the client module of the application.
The game also has a text version and a graphical version made using SDL2.

## Folder organization
```
- Assets: This is where you'll find all the resources you need for the game (SDL textures, .txt files with map data, etc.).
- Bin: Several executables will be produced in the bin folder:
	1. bin/deckTest: Test of the deckBuilder module, which allows users to customize their decks.
	2. bin/mainTest: Module containing the text versions of the different versions of the game (local or LAN).
	3. bin/main2D: Module containing the SDL version of the game.
- Doc: Code documentation.
- Include: Folder containing the SDL_net library.
- Obj: Folder containing the various .obj files.
- Src: .cpp and .h files containing the application code.
```
## Authors
Nicolas Patino
Juan C. Lenis


