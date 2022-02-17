CC = g++
CFLAGS = -Wall -c
SDLLIB = -lSDL2 -lSDL2_ttf -lSDL2_image

all: bin/main bin/mainConsole

bin/main: obj/main.o obj/game.o
	$(CC) -g obj/main.o obj/game.o $(SDLLIB) -o bin/main

bin/mainConsole: obj/mainConsole.o obj/gameBoard.o obj/gameSquare.o obj/unit.o obj/cardLib.o obj/card.o
	$(CC) -g obj/mainConsole.o obj/gameBoard.o obj/gameSquare.o obj/unit.o obj/cardLib.o obj/card.o -o bin/mainConsole

obj/main.o: src/main.cpp src/game.h
	$(CC) -o obj/main.o $(CFLAGS) src/main.cpp

obj/mainConsole.o: src/mainConsole.cpp src/gameBoard.h src/gameSquare.h src/unit.h src/cardLib.h src/card.h
	$(CC) -o obj/mainConsole.o $(CFLAGS) src/mainConsole.cpp

obj/game.o: src/game.h src/game.cpp
	$(CC) -o obj/game.o $(CFLAGS) src/game.cpp

obj/gameBoard.o: src/gameBoard.h src/gameBoard.cpp src/gameSquare.h src/unit.h src/cardLib.h src/card.h
	$(CC) -o obj/gameBoard.o $(CFLAGS) src/gameBoard.cpp

obj/gameSquare.o: src/gameSquare.h src/gameSquare.cpp src/unit.h src/cardLib.h src/card.h
	$(CC) -o obj/gameSquare.o $(CFLAGS) src/gameSquare.cpp

obj/unit.o: src/unit.h src/unit.cpp src/cardLib.h src/card.h
	$(CC) -o obj/unit.o $(CFLAGS) src/unit.cpp

obj/cardLib.o: src/cardLib.h src/cardLib.cpp src/card.h
	$(CC) -o obj/cardLib.o $(CFLAGS) src/cardLib.cpp

obj/card.o: src/card.h src/card.cpp
	$(CC) -o obj/card.o $(CFLAGS) src/card.cpp

clean:
	rm obj/*.o bin/main bin/mainConsole