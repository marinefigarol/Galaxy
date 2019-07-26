CC = gcc
CFLAGS = -c -Wall -ansi

all: main

alea.o: alea.c
	$(CC) alea.c $(CFLAGS)
	
home.o: home.c
	$(CC) home.c init_game.c alea.c $(CFLAGS)
	
init_game.o: init_game.c
	$(CC) init_game.c home.c alea.c menu.c $(CFLAGS)
	
ai.o: ai.c
	$(CC) ai.c init_game.c move_ships_ai.c $(CFLAGS)
	
menu.o: menu.c
	$(CC) menu.c move_fleet.c planet.c move_fleet.c show_galaxy.c quit.c turn.c $(CFLAGS)

move_fleet.o: move_fleet.c
	$(CC) move_fleet.c $(CFLAGS)
	
move_ships_ai.o: move_ships_ai.c
	$(CC) move_ships_ai.c ai.c init_game.c $(CFLAGS)
	
planet.o: planet.c
	$(CC) planet.c $(CFLAGS)
	
available_fleet.o: available_fleet.c
	$(CC) available_fleet.c init_game.c home.c $(CFLAGS)
	
show_galaxy.o: show_galaxy.c
	$(CC) show_galaxy.c $(CFLAGS)
	
quit.o: quit.c
	$(CC) quit.c $(CFLAGS)
	
turn.o: turn.c
	$(CC) turn.c ai.c $(CFLAGS)
    
main.o: main.c
	$(CC) main.c $(CFLAGS)
	
cheat.o: cheat.c
	$(CC) cheat.c $(CFLAGS)
	

main: main.o alea.o home.o init_game.o ai.o menu.o move_fleet.o move_ships_ai.o planet.o available_fleet.o show_galaxy.o quit.o turn.o cheat.o
	$(CC) main.o alea.o home.c init_game.o ai.o menu.o move_fleet.o move_ships_ai.o planet.o available_fleet.o show_galaxy.o quit.o turn.o cheat.o -o main
    

clean:
	rm *o

mrproper:
	rm *o main
