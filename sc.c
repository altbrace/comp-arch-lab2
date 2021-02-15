#include <stdio.h>
#include <stdint.h>
#include "sc.h"

#define FIRST_BIT 0b00010000
#define SECOND_BIT 0b00001000
#define THIRD_BIT 0b00000100
#define FOURTH_BIT 0b00000010
#define FIFTH_BIT 0b00000001

extern int memory[100];
extern uint8_t flags;

int sc_memoryInit() {
	
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

	*val = memory[addr];

	return 0;
}

int sc_memorySave(char* filename) {
	
	FILE* file = fopen(filename, "wb");
	if (file == NULL) return -1;

	size_t count = fwrite(memory, sizeof(int), 100, file);
	fclose(file);

	if (count != 100) return -1;

	return 0;
}

int sc_memoryLoad(char* filename) {
	
	FILE* file = fopen(filename, "rb");
	if (file == NULL) return -1;

	size_t count = fread(memory, sizeof(int), 100, file);
	fclose(file);

	if (count != 100) return -1;

	return 0;
}

int sc_regInit(void) {
	
	flags = 0b00000000;
	return 0;
}

int sc_regSet(uint8_t reg, int value) {
	
	if (value == 1) flags |= reg;
	else if (value == 0) flags = flags & (~reg);
	else return -1;

	return 0;
}

int sc_regGet(uint8_t reg, int* value) {

	if ((reg & flags) != 0) *value = 1;
	else return -1;

	return 0;
}

int sc_commandEncode(int command, int operand, int* value) {
	
	if (command > 76 || command < 10) return -1;
	if (operand > 127 || operand < 0) return -1;

	*value = 0b000000000000000;
	*value |= (command << 7);
	*value |= operand;

	return 0;

}

int sc_commandDecode(int value, int* command, int* operand) {

	if ((value >> 14) != 0) return -1;

	*operand = value & 0b000000001111111;
	*command = (value >> 7) & 0b000000001111111;

	return 0;
}
