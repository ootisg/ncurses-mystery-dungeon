#include "game_loop.h"

#include "menu.h"

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
	
	//Do stuff
	menu* m = malloc (sizeof (menu));
	m->x = 2;
	m->y = 2;
	m->width = 12;
	m->height = 24;
	m->options_text = malloc (sizeof (char*) * 24);
	m->selection_funcs = malloc (sizeof (void*) * 24);
	int i;
	for (i = 0; i < 24; i++) {
		m->options_text[i] = "Hello!";
		m->selection_funcs[i] = helloworld;
	}

	//Wait and end
	char c = 0;
	while (c != 'q') {
		clear ();
		menu_draw (m);
		c = getch ();
		if (c == 'w') {
			menu_offset_cursor (m, -1);
		} else if (c == 'a') {
			m->width--;
		} else if (c == 's') {
			menu_offset_cursor (m, 1);
		} else if (c == 'd') {
			m->width++;
		} else if (c == 't') {
			menu_do_select (m);
		}
	}
	endwin ();
	
}
