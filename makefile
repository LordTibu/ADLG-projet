CC = g++
CFLAGS = -Wall -c
SDLLIB = -lSDL2 -lSDL2_ttf -lSDL2_image
OBJPATH = ./obj
OBJ = $(OBJPATH)/*.o

all: main mainConsole

main: $(OBJPATH)/*.o
	$(CC) -g obj/main.o obj/game.o $(SDLLIB) -o bin/main

mainConsole: mainConsole.o gameBoard.o gameSquare.o unit.o cardLib.o card.o
	$(CC) -g obj/mainConsole.o obj/gameBoard.o obj/gameSquare.o obj/unit.o obj/cardLib.o obj/card.o -o bin/mainConsole

main.o: src/main.cpp src/game.h
	$(CC) -o obj/main.o $(CFLAGS) src/main.cpp

mainConsole.o: src/mainConsole.cpp src/gameBoard.h src/gameSquare.h src/unit.h src/cardLib.h src/card.h
	$(CC) -o obj/mainConsole.o $(CFLAGS) src/mainConsole.cpp

game.o: src/game.h src/game.cpp
	$(CC) -o obj/game.o $(CFLAGS) src/game.cpp

gameBoard.o: src/gameBoard.h src/gameBoard.cpp src/gameSquare.h src/unit.h src/cardLib.h src/card.h
	$(CC) -o obj/gameBoard.o $(CFLAGS) src/gameBoard.cpp

gameSquare.o: src/gameSquare.h src/gameSquare.cpp src/unit.h src/cardLib.h src/card.h
	$(CC) -o obj/gameSquare.o $(CFLAGS) src/gameSquare.cpp

unit.o: src/unit.h src/unit.cpp src/cardLib.h src/card.h
	$(CC) -o obj/unit.o $(CFLAGS) src/unit.cpp

cardLib.o: src/cardLib.h src/cardLib.cpp src/card.h
	$(CC) -o obj/cardLib.o $(CFLAGS) src/cardLib.cpp

card.o: src/card.h src/card.cpp
	$(CC) -o obj/card.o $(CFLAGS) src/card.cpp

clean:
	rm obj/*.o bin/main bin/mainConsole