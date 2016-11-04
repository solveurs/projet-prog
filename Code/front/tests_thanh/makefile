
# gcc Test.c -o prog `pkg-config --cflags --libs gtk+-3.0` `pkg-config --cflags cairo`


#
# Variables:
#
CC = gcc
BIN = tmpMemo
SRC = tmpMemo.c
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

CFLAGS = $(ERROR_FLAGS) `pkg-config --cflags --libs $(GLIB_CFLAGS) $(PANGO_CFLAGS) $(GTK_CFLAGS) $(CAIRO_CFLAGS)` -lm


#
# Construction du programme:
#

all: $(BIN)


# Compile :
$(BIN): $(SRC)
	$(CC) $(SRC) -o $(BIN) $(CFLAGS)


#
# Nettoyage:
#
clean:
	rm -f *.o *~ core $(BIN)
