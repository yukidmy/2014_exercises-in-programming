CC=gcc -g
RM=rm
CFLAGS= -I.
HEADERS= bidlist.h event.h  movingobject.h object.h  scenario.h  vector2.h \
 gameio.h  movingobjectmanager.h screen.h walls.h enemy.h goal.h gameover.h myenemy.h \
 enemy09.h hiraga.h superunk.h superunk2.h superunk3.h wey.h momoenemy.h \
 enemy26.h enemy37.h item.h random.h
OBJS= gameio.o screen.o walls.o vector2.o object.o movingobject.o
OBJSPLUS= $(OBJS) movingobjectmanager.o bidlist.o event.o scenario.o enemy.o \
 goal.o gameover.o enemy09.o hiraga.o superunk.o superunk2.o superunk3.o \
 wey.o momoenemy.o enemy26.o enemy37.o item.o random.o

.SUFFIXES: .c .o

.PHONY: clean

.c.o: $(HEADERS)
	$(CC) -c $(CFLAGS) $<

all: game2
	./game2

game2: $(OBJSPLUS) gamemain2.o 
	$(CC) -o $@ $^ -lcurses

debug: $(OBJSPLUS) log.o gamemain2.o 
	$(CC) -o $@ $^ -lcurses

game1: game
	./game

game: $(OBJSPLUS) gamemain.o 
	$(CC) -o $@ $^ -lcurses

clean:
	$(RM) -rf *.o game game2 debug
