#include <stdlib.h>
#include "myTerm/myTerm.h"
#include "myReadkey/rk.h"
#include "myBigChars/mbc.h"
#include "SimpleComputer/sc.h"

void init() {

	system("resize -s 27 95");
	system("clear");
	
	bc_box(1, 1, 60, 17);
	mt_gotoXY(26, 1);
	printf(" Memory ");

	bc_box(62, 1, 94, 5);
	mt_gotoXY(72, 1);
	printf(" accumulator ");

	bc_box(62, 5, 94, 9);
	mt_gotoXY(69, 5);
	printf(" instructionCounter ");
	
	bc_box(62, 9, 94, 13);
	mt_gotoXY(72, 9);
	printf(" Operation ");

	bc_box(62, 13, 94, 17);
	mt_gotoXY(75, 13);
	printf(" Flags ");

}
void mem_refresh() {
	
	mt_gotoXY(2, 2);
	char *memS[100];

	for (int i = 0; i < MEMORY_SIZE; i++) {
		if (memA[i] < 10) memS[i] = "+000%d" memA[i];
		else if (memA[i] < 100) memS[i] = "+00%d" memA[i];
		else if (memA[i] < 1000) memS[i] = "+0%d" memA[i];
		else memS[i] = "+%d" memA[i];
	}
	
	for (int i = 0; i < 10; i++) {
		mt_gotoXY(1, 2+i);

		for (int j = 0; j < 10; j++) printf("%s", memS[i*10+j]);
		
	}
} 

void main() {
	init();
	mem_refresh();
	scanf("%d");
}
