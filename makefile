CC := g++
CFLAGS := -Wall
SDLLIB := -lSDL2 -lSDL2_ttf -lSDL2_image
EXECS_PATH := ./bin
EXECS := $(EXECS_PATH)/main $(EXECS_PATH)/mainConsole $(EXECS_PATH)/mainTest $(EXECS_PATH)/deckTest
SRCS := $(wildcard src/*.cpp)
OBJS := $(foreach i, $(SRCS), $(patsubst src/%.cpp, obj/%.o, $(i)))
MAINOBJS := obj/main.o obj/game.o
MAINCONSOLEOBJS := obj/mainConsole.o obj/gameBoard.o obj/gameSquare.o obj/unit.o obj/cardLib.o obj/card.o
MAINTESTOBJS := obj/mainGameTest.o obj/gameConsole.o obj/gameBoard.o obj/gameSquare.o obj/unit.o obj/cardLib.o obj/card.o
DECKOBJS := obj/deckTest.o obj/deckBuilder.o obj/cardLib.o obj/card.o

all: $(EXECS)

$(EXECS_PATH)/main: $(MAINOBJS)
	$(CC) $(CFLAGS) -g $^ $(SDLLIB) -o $@

$(EXECS_PATH)/mainConsole: $(MAINCONSOLEOBJS)
	$(CC) $(CFLAGS) -g $^ -o $@

$(EXECS_PATH)/mainTest: $(MAINTESTOBJS)
	$(CC) $(CFLAGS) -g $^ -o $@

$(EXECS_PATH)/deckTest: $(DECKOBJS)
	$(CC) $(CFLAGS) -g $^ -o $@

obj/%.o: src/%.cpp src/*.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm obj/*.o $(EXECS)