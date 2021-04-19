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
	if ((y < rows) && (x < cols) && (x >= 0) && (y >= 0))
	{
		printf("\E[%d;%dH", y, x);
		return 0;
	}
	else
		return 1;	
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

int mt_colorreset() {
	
	printf("\E[;0m");
	printf("\E[1;0m");
	return 0;
}
