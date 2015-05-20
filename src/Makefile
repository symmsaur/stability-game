IDIR = ../include

CC=gcc
CFLAGS=-Wall -Werror -I$(IDIR) $(shell sdl2-config --cflags)

ODIR = ../target

LIBS = $(shell sdl2-config --libs) -lSDL2_image

_DEPS = engine.h main.h
DEPS = $(patsubst %, $(IDIR)/%,$(_DEPS))

_OBJ = main.o engine.o
OBJ = $(patsubst %, $(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

