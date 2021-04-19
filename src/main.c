#include <stdlib.h>
#include <string.h>
#include "myTerm/myTerm.h"
#include "myReadkey/rk.h"
#include "myBigChars/mbc.h"
#include "SimpleComputer/sc.h"

void init() {

	system("resize -s 27 95");
	system("clear");
	
	bc_box(1, 1, 63, 17);
	mt_gotoXY(26, 1);
	printf(" Memory ");

	bc_box(63, 1, 94, 5);
	mt_gotoXY(72, 1);
	printf(" accumulator ");

	bc_box(63, 5, 94, 9);
	mt_gotoXY(69, 5);
	printf(" instructionCounter ");
	
	bc_box(63, 9, 94, 13);
	mt_gotoXY(72, 9);
	printf(" Operation ");

	bc_box(63, 13, 94, 17);
	mt_gotoXY(75, 13);
	printf(" Flags ");

	bc_box(1, 16, 43, 27);

	bc_box(63, 16, 94, 27);

}
extern int selected;
int selected = 0;

void mem_refresh(int key) {
	
	mt_gotoXY(2, 2);
	char memS[100][6];
	char *str = (char*)malloc(6);
	
	
	
	for (int i = 0; i < MEMORY_SIZE; i++) {
		if (memA[i] < 10) str = "+000";

		else if (memA[i] < 100) str = "+00";

		else if (memA[i] < 1000) str = "+0";

		else str = "+";
		
		sprintf(memS[i], "%s%d", str, memA[i]);
		enum colors blue = blue;
		enum colors red = red;
	}	
	enum colors black = black;
	enum colors white = white;	
	bc_printStr(memS[18], 2, 17, white, black);

	for (int i = 0; i < 10; i++) {
		mt_gotoXY(2, 3+i);

		for (int j = 0; j < 10; j++) printf("%s ", memS[i*10+j]);
		printf("\n");
		
	}
}

void keyworker() {
	
	int* key;

	while (1) {
		mt_gotoXY(1, 29);
		rk_readkey(key);

		switch (*key) {
			case KEY_down:

		}
	}
}
void main() {
	init();
	memA[5] = 12;
	memA[18] = 5;
	memA[3] = 302;
	memA[88] = 9999;
	mem_refresh();
	
	int* key;
	
	while (1) {
		mt_gotoXY(1, 29);
		rk_readkey(key);
	}
	scanf("%d");
}
