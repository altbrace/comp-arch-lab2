#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "myTerm.h"

int mt_clrscr(void) {

	printf("\E[H\E[2J");
	return 0;
}

int mt_gotoXY(int x, int y) {
	
	int rows, cols;
	mt_getscreensize(&rows, &cols);
	if (x > rows || y > cols) {
		x = rows;
		y = cols;
	};
		
	char* xs = (char*)malloc(sizeof(int));
	char* ys = (char*)malloc(sizeof(int));
	sprintf(xs, "%d", x);
	sprintf(ys, "%d", y);
//	itoa(x, xs, 10);
//	itoa(y, ys, 10);

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
	
	printf("\033[1;%dm", color);
	return 0;
}

int mt_setbgcolor(enum colors color) {

	printf("\E[;%dm", color+10);
	return 0;
}
