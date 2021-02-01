#include <stdlib.h>

#ifndef SC_H
#define SC_H
#define MEMORY_SIZE 100

int sc_memoryInit();
int sc_memorySet(int addr, int val);
int sc_memoryGet(int addr, int* val);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_regInit(void);
int sc_regSet(int reg, int val);
int sc_regGet(int reg, int* val);
int sc_commandEncode(int cmd, int operand, int* value);
int sc_commandDecode(int value, int* cmd, int* operand);


#endif
