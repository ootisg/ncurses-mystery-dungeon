#include "game_menu.h"
#include "menu.h"

#include <stdlib.h>
#include <ncurses.h>

//Top-level menu
menu* tlm;
menu* menus;
menu** sorted_menus;
int num_menus;

menu* item_menu;

//Menu callback funcs
void tlm_items_callback () {
	menus[1].visible = 1;
}

void tlm_moves_callback () {
	//TODO
}

void tlm_team_callback () {
	//TODO
}

void tlm_others_callback () {
	//TODO
}

void tlm_ground_callback () {
	//TODO
}

//Menu management funcs
menu* alloc_menu () {
	
	if (num_menus == MAX_NUM_MENUS) {
		return 0;
	} else {
		return &(menus[num_menus++]);
	}

}

void sort_menus () {

	int i, j;
	menu* smallest;
	for (i = 0; i < num_menus; i++) {
		sorted_menus[i] = &(menus[i]); 
	}
	smallest = sorted_menus[0];
	int num_swaps = -1; //Initial garbage value
	//Bubble sort is efficient for an almost in-order list
	while (num_swaps != 0) {
		num_swaps = 0;
		for (i = num_menus - 1; i > 0; i--) {
			menu* a = sorted_menus[i];
			menu* b = sorted_menus[i - 1];
			if (a->depth > b->depth) {
				sorted_menus[i] = b;
				sorted_menus[i - 1] = a;
				num_swaps++;
			}
		}
	}
}

void menus_init () {

	//MENU LISTS
	menus = malloc (sizeof (menu) * MAX_NUM_MENUS);
	sorted_menus = malloc (sizeof (void*) * MAX_NUM_MENUS);
	
	//TLM
	tlm = &(menus[0]);
	num_menus = 1;
	menu_init (tlm, 2, 2, 12, 7, 0.0);
	tlm->visible = 1;
	int i;
	for (i = 0; i < 5; i++) {
		tlm->options_text[i] = "--";
		tlm->selection_funcs[i] = NULL;
	}
	tlm->options_text[0] = "Moves";
	tlm->options_text[1] = "Items";
	tlm->options_text[2] = "Team";
	tlm->options_text[3] = "Others";
	tlm->options_text[4] = "Ground";
	tlm->selection_funcs[0] = tlm_moves_callback;
	tlm->selection_funcs[1] = tlm_items_callback;
	tlm->selection_funcs[2] = tlm_team_callback;
	tlm->selection_funcs[3] = tlm_others_callback;
	tlm->selection_funcs[4] = tlm_ground_callback;

	//ITEM MENU
	item_menu = alloc_menu ();
	menu_init (item_menu, 4, 4, 12, 12, 1.0);
	item_menu->visible = 0;
	for (i = 0; i < 10; i++) {
		item_menu->options_text[i] = "--";
		item_menu->selection_funcs[i] = NULL;
	}

	//

}

void menus_dispatch_key (char c) {
	
	sort_menus ();
	menu* m;
	int i;
	for (i = 0; i < num_menus; i++) {
		if (sorted_menus[i]->visible) {
			m = sorted_menus[i];
			break;
		}
	}
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
	
	sort_menus ();
	int i;
	for (i = num_menus - 1; i >= 0; i--) {
		if (sorted_menus[i]->visible) {
			menu_draw (sorted_menus[i]);
		}
	}

}

