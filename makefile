CC= g++
CFLAGS= -Wall -c
SDLLIB = -lSDL2 -lSDL2_ttf -lSDL2_image

all: main

main: main.o game.o
	$(CC) -g obj/main.o obj/game.o $(SDLLIB) -o bin/main

main.o: src/main.cpp src/game.h
	$(CC) -o obj/main.o $(CFLAGS) src/main.cpp

game.o: src/game.h src/game.cpp
	$(CC) -o obj/game.o $(CFLAGS) src/game.cpp

clean:
	rmv obj/*.o bin/main