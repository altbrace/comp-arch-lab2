#include <stdio.h>
#include "sc.h"

int sc_memoryInit() {
	
	extern int memory[100];

	for (int i = 0; i < 100; i++) memory[i] = 0;

	return 0;
}

int sc_memorySet(int addr, int val) {
	
	if (addr < 0 || addr > 99) return -1;
	
	memory[addr] = val;

	return 0;

}

int sc_memoryGet(int addr, int* val) {	
	
	if (addr < 0 || addr > 99) return -1;

	&val = memory[addr];

	return 0;
}

int sc_memorySave(char* filename) {
	
	FILE* file = fopen(filename, "wb");
	if (file == NULL) return -1;

	size_t count = fwrite(memory, sizeof(int), 1, file);
	fclose(file);

	if (count != 100) return -1;

	return 0;
}

