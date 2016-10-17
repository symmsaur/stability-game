IDIR = ../include

CC=gcc
CFLAGS=-I$(IDIR) $(shell sdl2-config --cflags)

ODIR = ../target

LIBS = $(shell sdl2-config --libs) -lSDL2_image

_DEPS = main.h game.h engine.h level.h editor.h collision.h fireguy.h solidgrunt.h interactions.h
DEPS = $(patsubst %, $(IDIR)/%,$(_DEPS))

_OBJ = main.o collision.o game.o engine.o level.o editor.o fireguy.o solidgrunt.o interactions.o
OBJ = $(patsubst %, $(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

$(ODIR)/main: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS) $(LIBS)

