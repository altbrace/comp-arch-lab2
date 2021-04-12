#include "mbc.h"
#include <stdlib.h>
#include <stdio.h>
#include "../myTerm/myTerm.h"
#include <string.h>

#define MASK 0b00000000000000000000000000000001


int bc_printA(char* str) {
	
	printf("\E(0%s\E(B", str);
	return 0;

}

int bc_box(int y1, int x1, int y2, int x2) {
	
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
	
	mt_gotoXY(y1, x1);
	
	bc_printA("l");
	for (int i = 0; i < (y2 - y1 - 2); i++) bc_printA("q");
	bc_printA("k");
	mt_gotoXY(y1, x1+1);
	
	for (int i = 0; i < (x2 - x1 - 2); i++) {
		bc_printA("x");
		for (int j = 0; j < (y2 - y1 - 2); j++) printf(" ");
		bc_printA("x");
		mt_gotoXY(y1, x1+1+i);
	}

	bc_printA("m");

	for (int i = 0; i < (y2 - y1 - 2); i++) bc_printA("q");

	bc_printA("j");

	return 0;
}

int bc_printbigchar(char ch, int x, int y, enum colors fgcolor, enum colors bgcolor) {
	
	
	int table[16][2] = {{606348348, 1009001508},
			    {269752336, 1007685648},
			    {1008738364, 1006896132},
			    {1008738364, 1008738336},
			    {1009001508, 538976288},
			    {1006896188, 1008738336},
			    {1006896188, 1009001508},
			    {538976316, 538976288},
			    {1009001532, 1009001508},
			    {1009001532, 1008738336},
			    {1008738364, 1009001508},
			    {1006896132, 1009001508},
			    {67372092, 1006896132},
			    {1008738336, 1009001508},
			    {1006896188, 1006896132},
			    {1006896188, 67372036}};

	if (ch < '0' || (ch > '9' && ch < 'a') || ch > 'f') {
		printf("Character '%c' is not supported.\n", ch);
	       	return -1;
	}
	
	int* chnum = malloc(8);

	if (ch >= '0' && ch <= '9') chnum = table[ch - '0'];
	else if (ch >= 'a' && ch <= 'f') chnum = table[ch - 'a' + 10];

	int rows, cols;
	mt_getscreensize(&rows, &cols);
	
	if (x > rows) x = 0;
	if (y > cols) y = 0;
	
	mt_setfgcolor(fgcolor);
	mt_setbgcolor(bgcolor);

	for (int i = 0; i < x; i++) printf("\n");	
	for (int i = 0; i < y; i++) printf(" ");
	
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < y; k++) printf(" ");

		for (int j = 0; j < 8; j++) {
			
			if ((chnum[0] & MASK) != 0) bc_printA("a");
			else printf(" ");
			chnum[0] >>= 1;
		}
		printf("\n");
	}

	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < y; k++) printf(" ");

		for (int j = 0; j < 8; j++) {
		
			if ((chnum[1] & MASK) != 0) bc_printA("a");
			else printf(" ");
			chnum[1] >>= 1;
		}
		printf("\n");
	}
	
//	printf("\n");
		
	return 0;
}

void bc_printStr(char* str, int x, int y, enum colors fgcolor, enum colors bgcolor) {
	
		
	int table[17][2] = {{606348348, 1009001508},
			    {269752336, 1007685648},
			    {1008738364, 1006896132},
			    {1008738364, 1008738336},
			    {1009001508, 538976288},
			    {1006896188, 1008738336},
			    {1006896188, 1009001508},
			    {538976316, 538976288},
			    {1009001532, 1009001508},
			    {1009001532, 1008738336},
			    {1008738364, 1009001508},
			    {1006896132, 1009001508},
			    {67372092, 1006896132},
			    {1008738336, 1009001508},
			    {1006896188, 1006896132},
			    {1006896188, 67372036},
			    {2115508224, 1579134}};

	int len = strlen(str);
	int** chnum = malloc(len * 8);
	
	for (int i = 0; i < len; i++) {

//		if (str[i] < '0' || (str[i] > '9' && str[i] < 'a') || str[i] > 'f' || str[i] != '+') {
//			printf("Character '%c' is not supported.\n", str[i]);
//		       	return;
//		}
	
		if (str[i] >= '0' && str[i] <= '9') chnum[i] = table[str[i] - '0'];
		else if (str[i] >= 'a' && str[i] <= 'f') chnum[i] = table[str[i] - 'a' + 10];
		else chnum[i] = table[16];
	}

	int rows, cols;
	mt_getscreensize(&rows, &cols);
	
	if (x > rows) x = 0;
	if (y > cols) y = 0;
	
	mt_setfgcolor(fgcolor);
	mt_setbgcolor(bgcolor);

	for (int i = 0; i < x; i++) printf("\n");	
	for (int i = 0; i < y; i++) printf(" ");
	
	int ch = 0;
	for (int i = 0; i < 4; i++) {
		
		for (int j = 0; j < len; j++) {
			ch = chnum[j][0] >> i * 8;
			for (int k = 0; k < y; k++) printf(" ");

			for (int l = 0; l < 8; l++) {
				if ((ch & MASK) != 0) bc_printA("a");
				else printf(" ");
				ch >>= 1;
			}
		}
		printf("\n");
	}

	
	for (int i = 0; i < 4; i++) {
		
		for (int j = 0; j < len; j++) {
			ch = chnum[j][1] >> i * 8;
			for (int k = 0; k < y; k++) printf(" ");

			for (int l = 0; l < 8; l++) {
				if ((ch & MASK) != 0) bc_printA("a");
				else printf(" ");
				ch >>= 1;
			}
		}
		printf("\n");
	}

	printf("\n");
	

}



void bc_writeToFile(char c, int x, int y, enum colors fgcolor, enum colors bgcolor, FILE* file) {
	
	
}
