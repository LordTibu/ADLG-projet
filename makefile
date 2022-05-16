CC := g++
CFLAGS := -Wall
SDLLIB := -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_net
EXECS_PATH := ./bin
EXECS := $(EXECS_PATH)/main $(EXECS_PATH)/mainTest $(EXECS_PATH)/deckTest $(EXECS_PATH)/main2D
SRCS := $(wildcard src/*.cpp)
OBJS := $(foreach i, $(SRCS), $(patsubst src/%.cpp, obj/%.o, $(i)))
#MAINCONSOLEOBJS := obj/mainConsole.o obj/gameBoard.o obj/gameSquare.o obj/unit.o obj/cardLib.o obj/card.o
MAINTESTOBJS := obj/mainGameTest.o obj/deckBuilder.o obj/gameConsole.o obj/gameBoard.o obj/gameSquare.o obj/unit.o obj/statusCodex.o obj/status.o obj/cardLib.o obj/card.o obj/server.o obj/client.o
DECKOBJS := obj/deckTest.o obj/deckBuilder.o obj/cardLib.o obj/card.o 
MAINCLIENTOBJS := obj/mainClient.o obj/client.o obj/gameConsole.o obj/gameBoard.o obj/gameSquare.o obj/unit.o obj/statusCodex.o obj/status.o obj/cardLib.o obj/card.o obj/server.o
MAINSERVEROBJS := obj/mainServer.o obj/server.o obj/gameConsole.o obj/gameBoard.o obj/gameSquare.o obj/unit.o obj/statusCodex.o obj/status.o obj/cardLib.o obj/card.o obj/client.o
MAIN2D := obj/main2D.o obj/affichage2D.o obj/game2D.o obj/gameConsole.o obj/gameBoard.o obj/gameSquare.o obj/unit.o obj/statusCodex.o obj/status.o obj/cardLib.o obj/card.o obj/server.o obj/client.o

all: $(EXECS)

$(EXECS_PATH)/main2D: $(MAIN2D)
	$(CC) $(CFLAGS) -g $^ $(SDLLIB) -o $@

$(EXECS_PATH)/mainTest: $(MAINTESTOBJS)
	$(CC) $(CFLAGS) -g $^ $(SDLLIB) -o $@

$(EXECS_PATH)/deckTest: $(DECKOBJS)
	$(CC) $(CFLAGS) -g $^ -o $@

obj/%.o: src/%.cpp src/*.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm obj/*.o $(EXECS)