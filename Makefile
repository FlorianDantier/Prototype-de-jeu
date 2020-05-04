OBJ_FILES	=	./obj/main.o 		\
				./obj/Rectangle.o 	\
				./obj/Image.o 		\
				./obj/Character.o 	\
				./obj/SDL_Game.o 	\
				./obj/Game.o 		\
				./obj/Menu.o 		\
				./obj/Map.o 		\
				./obj/Button.o 		\
				./obj/Object.o 		\
				./obj/Player.o 		\
				./obj/Enemy.o


EXEC_NAME	=	./bin/game

CFLAGS	=	-Wall

CC	=	g++

LINKER_FLAGS	=	-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all:	$(EXEC_NAME)

$(EXEC_NAME):	$(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC_NAME) $(LINKER_FLAGS)

./obj/Rectangle.o:	./src/Rectangle.cpp ./src/Rectangle.h
	$(CC) $(CFLAGS) -c ./src/Rectangle.cpp -o ./obj/Rectangle.o

./obj/Image.o: 	./src/Image.cpp ./src/Image.h
	$(CC) $(CFLAGS) -c ./src/Image.cpp -o ./obj/Image.o

./obj/Button.o:		./src/Button.cpp ./src/Button.h
	$(CC) $(CFLAGS) -c ./src/Button.cpp -o ./obj/Button.o

./obj/Character.o:	./src/Character.cpp ./src/Character.h
	$(CC) $(CFLAGS) -c ./src/Character.cpp -o ./obj/Character.o

./obj/main.o:	./src/main.cpp
	$(CC) $(CFLAGS) -c ./src/main.cpp -o ./obj/main.o

./obj/SDL_Game.o:	./src/SDL_Game.cpp ./src/SDL_Game.h
	$(CC) $(CFLAGS) -c ./src/SDL_Game.cpp -o ./obj/SDL_Game.o

./obj/Game.o:	./src/Game.cpp ./src/Game.h
	$(CC) $(CFLAGS) -c ./src/Game.cpp -o ./obj/Game.o

./obj/Menu.o:	./src/Menu.cpp ./src/Menu.h
	$(CC) $(CFLAGS) -c ./src/Menu.cpp -o ./obj/Menu.o

./obj/Object.o:	./src/Object.cpp ./src/Object.h
	$(CC) $(CFLAGS) -c ./src/Object.cpp -o ./obj/Object.o

./obj/Player.o:	./src/Player.cpp ./src/Player.h
	$(CC) $(CFLAGS) -c ./src/Player.cpp -o ./obj/Player.o

./obj/Enemy.o:	./src/Enemy.cpp ./src/Enemy.h
	$(CC) $(CFLAGS) -c ./src/Enemy.cpp -o ./obj/Enemy.o

./obj/Map.o:	./src/Map.cpp ./src/Map.h
	$(CC) $(CFLAGS) -c ./src/Map.cpp -o ./obj/Map.o

clean:
	rm ./obj/*
	rm ./bin/*
