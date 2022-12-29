#include "menu.h"

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

menu* menu_init (void* loc, int x, int y, int width, int height, float depth) {
	
	//Initialize location/dimensions
	menu* ptr = (menu*)loc;
	ptr->x = x;
	ptr->y = y;
	ptr->width = width;
	ptr->height = height;
	ptr->depth = depth;

	//Initialize lists
	ptr->options_text = malloc (sizeof (char*) * (height - 2));
	ptr->selection_funcs = malloc (sizeof (void*) * (height - 2));
	ptr->selected_index = 0;

	//Return the new menu
	return ptr;

}

void menu_draw (menu* m) {

	int wx, wy;
	for (wy = 0; wy < m->height; wy++) {
		for (wx = 0; wx < m->width; wx++) {
			move (wy + m->y, wx + m->x);
			int top = wy == 0;
			int bottom = wy == m->height - 1;
			int left = wx == 0;
			int right = wx == m->width - 1;
			if (top && left || top && right || bottom && left || bottom && right) {
				addch ('+');
			} else if (top || bottom) {
				addch ('-');
			} else if (left || right) {
				addch ('|');
			} else {
				int t_pos = wx - 1;
				if (t_pos >= 0) {

					//Enable highlight if selected
					if (wy - 1 == m->selected_index) {
						attron (COLOR_PAIR (1));
					} else {
						attron (COLOR_PAIR (0));
					}

					char* str = m->options_text[wy - 1];
					if (t_pos < strlen (str)) {
						char c = str[t_pos];
						addch (c);
					} else {
						addch (' ');
					}

					//Disable highlight
					if (wy - 1 == m->selected_index) {
						attroff (COLOR_PAIR (1));
					} else {
						attroff (COLOR_PAIR (0));
					}

				} else {
					addch (' ');
				}
			}
		}
	}

}

void hello_world () {
	printw ("Hello World!\n");
}

void menu_do_select (menu* m) {
	if (m->selection_funcs[m->selected_index]) {
		m->selection_funcs[m->selected_index]();
	}
}

void menu_move_cursor (menu* m, int position) {
	m->selected_index = position;
}

void menu_offset_cursor (menu* m, int offset) {
	m->selected_index += offset;
	if (m->selected_index < 0) {
		m->selected_index = 0;
	}
	if (m->selected_index > m->height - 3) {
		m->selected_index = m->height - 3;
	}
}
