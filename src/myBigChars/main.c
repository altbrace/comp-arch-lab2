#include <stdio.h>
#include "mbc.h"

void main() {
	
	bc_printA("0123456789abcdefghijklmnopqrstuvwxyz");

	printf("\n");
	bc_box(10, 10, 30, 50);
	printf("\n");
	
	enum colors blue = blue;
	enum colors red = red;
	
	char* str = "0123456789abcdef";
	
	for (int i=0; i<16; i++) {
		bc_printbigchar(str[i], 0, 0, blue, red);
		printf("\n");
	}	
//	bc_printStr("dadada123");

}
