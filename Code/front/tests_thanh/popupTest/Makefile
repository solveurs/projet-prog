CC=gcc
CFLAGS = -W -Wall -g `pkg-config --cflags cairo`
LDFLAGS=
EXEC=main

all: $(EXEC)

$(EXEC): main.o widgets.o
		$(CC) `pkg-config --cflags --libs gtk+-3.0` -o $@ $^ $(LDFLAGS)

main.o: main.c widgets.h
		$(CC) `pkg-config --cflags --libs gtk+-3.0` -o $@ -c $< $(CFLAGS)

widgets.o: widgets.c widgets.h
		$(CC) `pkg-config --cflags --libs gtk+-3.0` -o $@ -c $< $(CFLAGS)
		
clear:
		rm *.o
		rm $(EXEC)

