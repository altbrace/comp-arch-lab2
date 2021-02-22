#include <stdio.h>

#ifndef MBC_H
#define MBC_H

int bc_printA(char* str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(char c, int x, int y, enum colors color, enum colors color);
int bc_setbigcharpos(int* big)
