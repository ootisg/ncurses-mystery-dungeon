#include "game_menu.h"
#include "menu.h"

#include <stdlib.h>
#include <ncurses.h>

//Top-level menu
menu* tlm;
menu* menus;
menu* sorted_menus;
int num_menus;

void menus_init () {

	menus = malloc (sizeof (menu) * MAX_NUM_MENUS);
	tlm = &(menus[0]);
	num_menus = 1;
	menu_init (tlm, 2, 2, 12, 12, 0.0);
	int i;
	for (i = 0; i < 10; i++) {
		tlm->options_text[i] = "Hello!";
		tlm->selection_funcs = NULL;
	}

}

void menus_dispatch_key (char c) {
	
	menu* m = tlm;
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

void menus_draw () {
	
	menu_draw (tlm);

}

void sort_menus () {



}
