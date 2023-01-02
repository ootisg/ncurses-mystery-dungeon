#include "game_loop.h"

#include "menu.h"
#include "game_menu.h"

#include <stdlib.h>
#include <ncurses.h>

void helloworld () {
	//Do nothing
	return;
}

int main () {
	
	//Init curses
	initscr ();
	raw ();
	noecho ();
	keypad (stdscr, 1);
	//Colors
	if (has_colors ()) {
		start_color ();
		init_pair (0, 0, 1);
		init_pair (1, 0, 7);
	}

	menus_init ();

	//Wait and end
	char c = 0;
	while (c != 'q') {
		clear ();
		menus_dispatch_key (c);
		menus_draw ();
		c = getch ();
	}
	endwin ();
	
}
