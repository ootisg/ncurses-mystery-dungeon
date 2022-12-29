#include "game_menu.h"
#include "menu.h"

#include <stdlib.h>

//Top-level menu
menu* tlm;

void menus_init () {

	tlm = malloc (sizeof (menu));
	menu_init (tlm, 2, 2, 12, 12, 0.0);
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
