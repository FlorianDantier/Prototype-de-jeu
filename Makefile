OBJ_FILES	=	./obj/main.o 	\
				./obj/Game.o

EXEC_NAME	=	./bin/game

CFLAGS	=	-Wall -ggdb

CC	=	g++

LINKER_FLAGS	=	-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all:	$(EXEC_NAME)

$(EXEC_NAME):	$(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC_NAME) $(LINKER_FLAGS)

./obj/main.o:	./src/main.cpp
	$(CC) $(CFLAGS) -c ./src/main.cpp -o ./obj/main.o

./obj/Game.o:	./src/Game.cpp ./src/Game.hpp
	$(CC) $(CFLAGS) -c ./src/Game.cpp -o ./obj/Game.o

clean:
	rm ./obj/*
	rm ./bin/*