#include <stdlib.h>
#include <stdint.h>

#ifndef SC_H
#define SC_H
#define MEMORY_SIZE 100


#define FIRST_BIT 0b00010000
#define SECOND_BIT 0b00001000
#define THIRD_BIT 0b00000100
#define FOURTH_BIT 0b00000010
#define FIFTH_BIT 0b00000001


extern int memA[];
extern uint8_t flags;
int sc_memoryInit();
int sc_memorySet(int addr, int val);
int sc_memoryGet(int addr, int* val);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_memoryReset();
int sc_regInit(void);
int sc_regSet(uint8_t reg, int val);
int sc_regGet(uint8_t reg);
int sc_commandEncode(int cmd, int operand, int* value);
int sc_commandDecode(int value, int* cmd, int* operand);


#endif
