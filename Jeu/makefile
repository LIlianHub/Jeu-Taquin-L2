Jeu:main.o animation.o tableau.o mouvement.o
	gcc -o Jeu mouvement.o animation.o main.o tableau.o `sdl-config --cflags --libs` -lSDL -l SDL_ttf

tableau.o:tableau.c mouvement.h
	gcc -o tableau.o -c tableau.c -Wall -Wextra
	
mouvement.o:mouvement.c
	gcc -o mouvement.o -c mouvement.c -Wall -Wextra

animation.o:animation.c mouvement.h tableau.h
	gcc -c animation.c -Wall -Wextra -o animation.o `sdl-config --cflags --libs` -lSDL -l SDL_ttf

main.o:main.c mouvement.h tableau.h animation.h
	gcc -c main.c -Wall -Wextra -o main.o `sdl-config --cflags --libs` -lSDL -l SDL_ttf


