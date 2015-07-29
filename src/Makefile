IDIR = ../include

CC=gcc
CFLAGS=-Wall -Werror -I$(IDIR) $(shell sdl2-config --cflags)

ODIR = ../target

LIBS = $(shell sdl2-config --libs) -lSDL2_image

_DEPS = main.h game.h engine.h level.h editor.h actor.h
DEPS = $(patsubst %, $(IDIR)/%,$(_DEPS))

_OBJ = main.o game.o engine.o level.o editor.o actor.o
OBJ = $(patsubst %, $(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

$(ODIR)/main: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS) $(LIBS)

