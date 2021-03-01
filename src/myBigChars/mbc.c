#include "mbc.h"
#include <stdlib.h>
#include <stdio.h>
#include "../myTerm/myTerm.h"

int bc_printA(char* str) {
	
	printf("\E(0%s\E(B", str);
	return 0;

}

int bc_box(int x1, int y1, int x2, int y2) {
	
	if (x1 > x2 || y1 > y2) {
		printf("bc_box: coordinates should be left upper corner (x1, y1) and right bottom corner (x2, y2)\n");
		return -1;
	}
	int rows = 0;
	int cols = 0;

	mt_getscreensize(&rows, &cols);

	if ((x2 - x1) > rows) {
		x1 = 0;
		x2 = rows;
	}

	if ((y2 - y1) > cols) {
		y1 = 0;
		y2 = cols;
	}
	
	mt_clrscr();
	
	for (int i = 0; i < y1; i++) printf(" ");

	bc_printA("l");
	for (int i = 0; i < (y2 - y1 - 2); i++) bc_printA("q");
	bc_printA("k");
	printf("\n");
	
	for (int i = 0; i < (x2 - x1 - 2); i++) {
		for (int j = 0; j < y1; j++) printf(" ");
		bc_printA("x");
		for (int j = 0; j < (y2 - y1 - 2); j++) printf(" ");
		bc_printA("x");
		printf("\n");
	}

	for (int i = 0; i < y1; i++) printf(" ");
	bc_printA("m");

	for (int i = 0; i < (y2 - y1 - 2); i++) bc_printA("q");

	bc_printA("j");
	printf("\n");

	return 0;
}

int bc_printbigchar(char ch, int x, int y, enum colors fgcolor, enum colors bgcolor) {

	int table[16][2] = {{606348348, 1009001508},
			    {136845320, 1007159304},
			    {1006896188, 1008738336},
			    {1006896188, 1006896132},
			    {1009001508, 67372036},
			    {1008738364, 1006896132},
			    {1008738364, 606348348},
			    {67372092, 67372036},
			    {1009001532, 1009001508},
			    {1009001532, 1006896132},
			    {1006896188, 
	
}


