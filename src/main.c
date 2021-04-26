#include <stdlib.h>
#include <string.h>
#include "myTerm/myTerm.h"
#include "myReadkey/rk.h"
#include "myBigChars/mbc.h"
#include "SimpleComputer/sc.h"

extern int ic, acc;
int ic = 0;
int acc = 0;

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
	
	mt_gotoXY(76, 16);
	printf(" Keys ");
	
	mt_gotoXY(64, 17);
	printf("l - load");
	
	mt_gotoXY(64, 18);
	printf("s - save");
	
	mt_gotoXY(64, 19);
	printf("r - run");

	mt_gotoXY(64, 20);
	printf("t - step");

	mt_gotoXY(64, 21);
	printf("i - reset");

	mt_gotoXY(64, 22);
	printf("F5 - accumulator");

	mt_gotoXY(64, 23);
	printf("F6 - instructionCounter");

}

void mem_refresh() {
	
	mt_gotoXY(2, 2);
	char memS[100][6];
	char *str = (char*)malloc(6);
	enum colors black = black;
	enum colors white = white;
	enum colors blue = blue;
	enum colors red = red;
	
	for (int i = 0; i < MEMORY_SIZE; i++) {
		if (memA[i] < 10) str = "+000";

		else if (memA[i] < 100) str = "+00";

		else if (memA[i] < 1000) str = "+0";

		else str = "+";
		
		sprintf(memS[i], "%s%d", str, memA[i]);
	}	

	bc_printStr(memS[ic], 2, 17, white, black);
	
	mt_gotoXY(76, 2);
	printf("      ");
	mt_gotoXY(78, 2);
	printf("%d", acc);

	mt_gotoXY(76, 6);
	printf("     ");
	mt_gotoXY(78, 6);
	printf("%d", ic);

	for (int i = 0; i < 10; i++) {
		mt_gotoXY(2, 3+i);

		for (int j = 0; j < 10; j++) {
			if ((i * 10 + j) == ic) mt_setfgcolor(white);
			printf("%s ", memS[i*10+j]);
			mt_colorreset();
		}

		printf("\n");
		
	}
}

void keyworker() {
	
	int key = 0;

	while (1) {
		mt_gotoXY(1, 29);
		rk_readkey(&key);

		if (key == KEY_down && ic <= 89) ic += 10;

		else if ((key == KEY_right) && (ic <= 98)) ic += 1;

		else if ((key == KEY_up) && (ic >= 10)) ic -= 10; 

		else if ((key == KEY_left) && (ic >= 1)) ic -= 1;

		else if (key == KEY_l) mem_load();

		else if (key == KEY_s) mem_save();

		else if (key == KEY_i) mem_reset();

		else if (key == KEY_f5) acc = memA[ic];

		else if (key == KEY_f6) {
			int k = 0;
			scanf("%d", &k);
			if ((k > 0) && (k < 100)) ic = k;
		}
			
		mem_refresh();

		
	}
}

void mem_reset() {

	for (int i = 0; i < 100; i++) memA[i] = 0;
}

void mem_load() {

	FILE* file = fopen("memory.db", "rb");
	if (file == NULL) return;

	fread(memA, sizeof(int), 100, file);
	fclose(file);
}

void mem_save() {
	
	FILE* file = fopen("memory.db", "wb");
	if (file == NULL) return;

	fwrite(memA, sizeof(int), 100, file);
	fclose(file);
}


void main() {
	init();
//	memA[5] = 12;
//	memA[10] = 444;
//	memA[18] = 5;
//	memA[3] = 302;
//	memA[88] = 9999;
	mem_refresh();
	
	keyworker();	
//	scanf("%d");
}
