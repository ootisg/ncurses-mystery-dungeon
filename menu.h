#ifndef MENU_H
#define MENU_H

struct menu {

	//Positioning information
	int x;
	int y;
	int width;
	int height; //Menu bounds
	float depth; //Depth for layering

	//Selection information
	char** options_text; //Display text
	void (**selection_funcs)(); //Selection callback funcs
	void* menu_data; //Additional menu-specific data
	int selected_index; //The currentlty selected index

};

typedef struct menu menu;

menu* menu_init (void* loc, int x, int y, int width, int height, float depth);
void menu_move_cursor (menu* m, int position);
void menu_offset_cursor (menu* m, int offset);
void menu_do_select (menu* m);
void menu_draw (menu* m);
void menu_draw_all (menu** marr, int num_menus);

#endif
