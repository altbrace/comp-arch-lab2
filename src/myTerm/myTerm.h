#include <stdio.h>
#ifndef MYTERM_H
#define MYTERM_H

enum colors {black = 30, red = 31, green = 32, 
	    yellow = 33, blue = 34, purple = 35,
	    cyan = 36, white = 37};

int mt_clrscr(void);
int mt_gotoXY(int x, int y);
int mt_getscreensize(int* rows, int* cols);
int mt_setfgcolor(enum colors);
int mt_setbgcolor(enum colors);
int mt_colorreset();

#endif
