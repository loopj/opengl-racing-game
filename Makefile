##########################
# foobar's Makefile      #
# Object Based version 2 #
##########################

CC  = gcc -Wall -ansi
BIN = race

all:
	@echo Building and Linking Race Game
	$(CC) src/main.c     -c `sdl-config --cflags`
	$(CC) src/timing.c   -c `sdl-config --cflags`
	$(CC) src/vector.c   -c `sdl-config --cflags`
	$(CC) src/fifo.c     -c `sdl-config --cflags`
	$(CC) src/ortho.c    -c `sdl-config --cflags`
	$(CC) src/audio.c    -c `sdl-config --cflags`
	$(CC) src/font.c     -c `sdl-config --cflags`
	$(CC) src/init.c     -c `sdl-config --cflags`
	$(CC) src/textures.c -c `sdl-config --cflags`
	$(CC) src/terrain.c  -c `sdl-config --cflags`	
	$(CC) src/menu.c     -c `sdl-config --cflags`
	$(CC) src/game.c     -c `sdl-config --cflags`
	$(CC) src/hud.c      -c `sdl-config --cflags`
	$(CC) src/messages.c -c `sdl-config --cflags`
	$(CC) src/camera.c   -c `sdl-config --cflags`

	$(CC) main.o timing.o vector.o fifo.o ortho.o audio.o font.o \
	init.o textures.o terrain.o menu.o game.o hud.o messages.o \
	camera.o \
	-o $(BIN) -framework GLUT -framework OpenGL -lSDL_image -lSDL_mixer -lm `sdl-config --libs`
	
	@rm -f *.o

clean:
	@echo Removing All Binaries
	@rm -f *.o
	@rm $(BIN)
	@echo Done.
