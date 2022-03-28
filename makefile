CC := g++
CFLAGS := -Wall
SDLLIB := -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_net
EXECS_PATH := ./bin
EXECS := $(EXECS_PATH)/main $(EXECS_PATH)/mainConsole $(EXECS_PATH)/mainTest $(EXECS_PATH)/deckTest $(EXECS_PATH)/mainServer $(EXECS_PATH)/mainClient
SRCS := $(wildcard src/*.cpp)
OBJS := $(foreach i, $(SRCS), $(patsubst src/%.cpp, obj/%.o, $(i)))
MAINOBJS := obj/main.o obj/game.o
MAINCONSOLEOBJS := obj/mainConsole.o obj/gameBoard.o obj/gameSquare.o obj/unit.o obj/cardLib.o obj/card.o
MAINTESTOBJS := obj/mainGameTest.o obj/gameConsole.o obj/gameBoard.o obj/gameSquare.o obj/unit.o obj/cardLib.o obj/card.o obj/server.o obj/client.o
DECKOBJS := obj/deckTest.o obj/deckBuilder.o obj/cardLib.o obj/card.o 
MAINCLIENTOBJS := obj/mainClient.o obj/client.o obj/gameConsole.o obj/gameBoard.o obj/gameSquare.o obj/unit.o obj/cardLib.o obj/card.o obj/server.o
MAINSERVEROBJS := obj/mainServer.o obj/server.o obj/gameConsole.o obj/gameBoard.o obj/gameSquare.o obj/unit.o obj/cardLib.o obj/card.o obj/client.o

all: $(EXECS)

$(EXECS_PATH)/main: $(MAINOBJS)
	$(CC) $(CFLAGS) -g $^ $(SDLLIB) -o $@

$(EXECS_PATH)/mainServer: $(MAINSERVEROBJS)
	$(CC) $(CFLAGS) -g $^ $(SDLLIB) -o $@

$(EXECS_PATH)/mainClient: $(MAINCLIENTOBJS)
	$(CC) $(CFLAGS) -g $^ $(SDLLIB) -o $@

$(EXECS_PATH)/mainConsole: $(MAINCONSOLEOBJS)
	$(CC) $(CFLAGS) -g $^ -o $@

$(EXECS_PATH)/mainTest: $(MAINTESTOBJS)
	$(CC) $(CFLAGS) -g $^ $(SDLLIB) -o $@

$(EXECS_PATH)/deckTest: $(DECKOBJS)
	$(CC) $(CFLAGS) -g $^ -o $@

obj/%.o: src/%.cpp src/*.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm obj/*.o $(EXECS)