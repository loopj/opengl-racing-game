##########################
# foobar's Makefile      #
# Object Based version 2 #
##########################

CC  = gcc -Wall -ansi
BIN = race

CFLAGS  = `sdl-config --cflags` -std=c99
LDFLAGS = `sdl-config --libs` -lSDL_image -lSDL_mixer -lm

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	LDFLAGS += -lGL -lGLU
endif
ifeq ($(UNAME), Darwin)
	LDFLAGS += -framework GLUT -framework OpenGL
endif
ifeq ($(UNAME), Cygwin)
	LDFLAGS += -lopengl32 -lglu32
endif

all:
	@echo Building and Linking Race Game
	$(CC) src/*.c $(CFLAGS) $(LDFLAGS) -o $(BIN)

clean:
	@echo Removing All Binaries
	@rm -f *.o $(BIN)
	@echo Done.