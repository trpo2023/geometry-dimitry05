all: Hallo_World
Hallo_World: Hallo_World.c
	gcc -Wall -Werror -o Hallo_World.exe  Hallo_World.c
clean:
	rm Hallo_World.exe
run:
	./Hallo_World.exe

