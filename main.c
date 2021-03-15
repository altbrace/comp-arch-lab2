#include "myTerm.h"
#include <stdio.h>

void main() {

	printf("to be cleared\n");
	int clr;
	scanf("%d", &clr);
	mt_clrscr();
	mt_gotoXY(4, 10);
	int rows = 0;
	int cols = 0;
	mt_getscreensize(&rows, &cols);
	printf("rows = %d, cols = %d\n", rows, cols);
	mt_setfgcolor(red);
	mt_setbgcolor(blue);
	printf("kek\n");

}
