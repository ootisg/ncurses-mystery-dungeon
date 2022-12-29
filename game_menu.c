#include "game_menu.h"

//Top-level menu
menu* tlm;

void menus_init () {

	tlm = malloc (sizeof (menu));
	init_menu (tlm, 2, 2, 12, 12);
	int i;
	for (i = 0; i < 10; i++) {
		tlm->options_text[i] = "Hello!";
		tlm->selection_funcs = NULL;
	}

}

void menus_dispatch_key (char c) {

}

void menus_draw () {

}
