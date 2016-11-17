CC=gcc
CFLAGS = -W -Wall -g `pkg-config --cflags cairo`
LDFLAGS=
EXEC=fentest

all: 		$(EXEC)
		rm *.o

$(EXEC): fentest.o widgets.o
		$(CC) `pkg-config --cflags --libs gtk+-3.0` -o $@ $^ $(LDFLAGS)

fentest.o: fentest.c widgets.h
		$(CC) `pkg-config --cflags --libs gtk+-3.0` -o $@ -c $< $(CFLAGS)

widgets.o: widgets.c widgets.h
		$(CC) `pkg-config --cflags --libs gtk+-3.0` -o $@ -c $< $(CFLAGS)
		
clear:
		rm $(EXEC)

