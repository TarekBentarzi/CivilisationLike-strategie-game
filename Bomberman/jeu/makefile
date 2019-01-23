EXEC=bomberman
SOURCES=main.c jeu.c bonus.c bombe.c menu.c
OBJECTS=$(SOURCES:.c=.o)
CC=gcc
CFLAGS= -Wall -std=gnu99 -Werror -g
 
.PHONY: default clean
 
default: $(EXEC)
 
main.o:jeu.c jeu.h bonus.c bonus.h bombe.c bombe.h menu.c menu.h

%.o: %.c
	$(CC) $< $(CFLAGS) -o $@ -c 
 
$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^
 
clean:
	rm -rf $(EXEC) $(OBJECTS) $(SOURCES:.c=.c~) $(SOURCES:.c=.h~) Makefile~
