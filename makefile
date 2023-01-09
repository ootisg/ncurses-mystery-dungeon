main: game_loop.c game_loop.h menu game_menu
	gcc -g game_loop.c menu.o game_menu.o -lncurses
menu: menu.c menu.h
	gcc -c -g menu.c
game_menu: game_menu.c game_menu.h
	gcc -c -g game_menu.c
