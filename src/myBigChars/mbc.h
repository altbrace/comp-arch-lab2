#include <stdio.h>
#include "../myTerm/myTerm.h"

#ifndef MBC_H
#define MBC_H

int bc_printA(char* str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(char c, int x, int y, enum colors fgcolor, enum colors bgcolor);
int bc_setbigcharpos(int* big, int x, int y, int value);
int bc_getbigcharpos(int* big, int x, int y, int* count);
int bc_bigcharwrite(FILE* file, int* big, int count);
int bc_bigcharread(FILE* file, int* big, int needed, int* read);

#endif
