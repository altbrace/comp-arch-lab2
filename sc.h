#include <stdlib.h>
#include <stdint.h>

#ifndef SC_H
#define SC_H
#define MEMORY_SIZE 100

/*
uint8_t FIRST_BIT = 0b00010000;
uint8_t SECOND_BIT = 0b00001000;
uint8_t THIRD_BIT = 0b00000100;
uint8_t FOURTH_BIT = 0b00000010;
uint8_t FIFTH_BIT = 0b00000001;
*/

int sc_memoryInit();
int sc_memorySet(int addr, int val);
int sc_memoryGet(int addr, int* val);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_regInit(void);
int sc_regSet(uint8_t reg, int val);
int sc_regGet(uint8_t reg, int* val);
int sc_commandEncode(int cmd, int operand, int* value);
int sc_commandDecode(int value, int* cmd, int* operand);


#endif
