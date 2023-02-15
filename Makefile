all: Hallo_World
Hallo_World: Hallo_World.c
	gcc -Wall -Werror -o Hallo_World Hallo_World.c
clean:
	rm Hallo_World
run:
	./Hallo_World
