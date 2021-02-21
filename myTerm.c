#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "myTerm.h"

int mt_clrscr(void) {

	printf("\033[2J");
	return 0;
}

int mt_gotoXY(int x, int y) {
	
	char* xs, ys;
	itoa(x, xs, 10);
	itoa(y, ys, 10);

	printf("\033[%s;%sH", xs, ys);
	return 0;
}

int mt_getscreensize(int* rows, int* cols) {

	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	*rows = w.ws_row;
	*cols = w.ws_col;

	return 0;
}

int mt_setfgcolor(enum colors color) {
	
	printf("\033[5;%d", color);
	return 0;
}

int mt_setbgcolor(enum colors color) {

	printf("\u001b")
}
