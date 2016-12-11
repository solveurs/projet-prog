
# gcc Test.c -o prog `pkg-config --cflags --libs gtk+-3.0` `pkg-config --cflags cairo`


#
# Variables:
#
CC = gcc
BIN = main
SRC = figures.c main.c
OBJ = $(SRC:.c=.o)


#
# Flags d'erreurs:
#
ERROR_FLAGS = -Wall -W -pedantic -g


#
# Flags pour le compilateur:
#
GLIB_CFLAGS = glib-2.0
PANGO_CFLAGS = pango
GTK_CFLAGS = gtk+-3.0
CAIRO_CFLAGS = cairo

CFLAGS = `pkg-config --cflags --libs $(GTK_CFLAGS) $(CAIRO_CFLAGS) $(GLIB_CFLAGS) $(PANGO_CFLAGS) ` -lm $(ERROR_FLAGS)


#
# Construction du programme:
#

all: $(BIN)


# Compile :
$(BIN): $(SRC)
	$(CC) $(SRC) -c $(CFLAGS)
	$(CC) $(OBJ) -o $(BIN) $(CFLAGS)

#
# Nettoyage:
#
clean:
	rm -f *.o *~ core $(BIN)
