CC=gcc
CFLAGS = -W -Wall -g `pkg-config --cflags cairo`
LDFLAGS=
EXEC=scroll

all: 		$(EXEC)
		rm *.o

$(EXEC): scroll.o widgets.o
		$(CC) `pkg-config --cflags --libs gtk+-3.0` -o $@ $^ $(LDFLAGS)

scroll.o: scroll.c widgets.h
		$(CC) `pkg-config --cflags --libs gtk+-3.0` -o $@ -c $< $(CFLAGS)

widgets.o: widgets.c widgets.h
		$(CC) `pkg-config --cflags --libs gtk+-3.0` -o $@ -c $< $(CFLAGS)
		
clear:
		rm $(EXEC)

