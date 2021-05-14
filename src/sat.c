#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SimpleComputer/sc.h"

int get_command(char* str) {
	
	if (strcmp(str, "READ") == 0 || strcmp(str, "read") == 0) return 10;
	else if (strcmp(str, "WRITE") == 0 || strcmp(str, "write") == 0) return 11;
	else if (strcmp(str, "LOAD") == 0 || strcmp(str, "load") == 0) return 20;
	else if (strcmp(str, "STORE") == 0 || strcmp(str, "store") == 0) return 21;
	else if (strcmp(str, "ADD") == 0 || strcmp(str, "add") == 0) return 30;
	else if (strcmp(str, "SUB") == 0 || strcmp(str, "sub") == 0) return 31;
	else if (strcmp(str, "DIVIDE") == 0 || strcmp(str, "divide") == 0) return 32;
	else if (strcmp(str, "MUL") == 0 || strcmp(str, "mul") == 0) return 33;
	else if (strcmp(str, "JUMP") == 0 || strcmp(str, "jump") == 0) return 40;
	else if (strcmp(str, "JNEG") == 0 || strcmp(str, "jneg") == 0) return 41;
	else if (strcmp(str, "JZ") == 0 || strcmp(str, "jz") == 0) return 42;
	else if (strcmp(str, "HALT") == 0 || strcmp(str, "halt") == 0) return 43;
	else if (strcmp(str, "NOT") == 0 || strcmp(str, "not") == 0) return 51;
	else if (strcmp(str, "AND") == 0 || strcmp(str, "and") == 0) return 52;
	else if (strcmp(str, "OR") == 0 || strcmp(str, "or") == 0) return 53;
	else if (strcmp(str, "XOR") == 0 || strcmp(str, "xor") == 0) return 54;
	else if (strcmp(str, "JNS") == 0 || strcmp(str, "jns") == 0) return 55;
	else if (strcmp(str, "JC") == 0 || strcmp(str, "jc") == 0) return 56;
	else if (strcmp(str, "JNC") == 0 || strcmp(str, "jnc") == 0) return 57;
	else if (strcmp(str, "JP") == 0 || strcmp(str, "jp") == 0) return 58;
	else if (strcmp(str, "JNP") == 0 || strcmp(str, "jnp") == 0) return 59;
	else if (strcmp(str, "CHL") == 0 || strcmp(str, "chl") == 0) return 60;
	else if (strcmp(str, "SHR") == 0 || strcmp(str, "shr") == 0) return 61;
	else if (strcmp(str, "RCL") == 0 || strcmp(str, "rcl") == 0) return 62;
	else if (strcmp(str, "RCR") == 0 || strcmp(str, "rcr") == 0) return 63;
	else if (strcmp(str, "NEG") == 0 || strcmp(str, "neg") == 0) return 64;
	else if (strcmp(str, "ADDC") == 0 || strcmp(str, "addc") == 0) return 65;
	else if (strcmp(str, "SUBC") == 0 || strcmp(str, "subc") == 0) return 66;
	else if (strcmp(str, "LOGLC") == 0 || strcmp(str, "loglc") == 0) return 67;
	else if (strcmp(str, "LOGRC") == 0 || strcmp(str, "logrc") == 0) return 68;
	else if (strcmp(str, "RCCL") == 0 || strcmp(str, "rccl") == 0) return 69;
	else if (strcmp(str, "RCCR") == 0 || strcmp(str, "rccr") == 0) return 70;
	else if (strcmp(str, "MOVA") == 0 || strcmp(str, "mova") == 0) return 71;
	else if (strcmp(str, "MOVR") == 0 || strcmp(str, "movr") == 0) return 72;
	else if (strcmp(str, "MOVCA") == 0 || strcmp(str, "movca") == 0) return 73;
	else if (strcmp(str, "MOVCR") == 0 || strcmp(str, "movcr") == 0) return 74;
	else if (strcmp(str, "ADDCA") == 0 || strcmp(str, "addca") == 0) return 75;
	else if (strcmp(str, "SUBCA") == 0 || strcmp(str, "subca") == 0) return 76;
	else if (strcmp(str, "=") == 0) return 99;
	else return 0;
}

int main(int argc, char **argv) {
	
	char *finname, *foutname;
	if (argc < 2 || argc > 3) {
		printf("Usage: ./sat [.sa file] [output file](optional)\n");
		return -1;	
	}
	
	finname = argv[1];
	if (argc == 2) foutname = "sc.out";
	else foutname = argv[2];

	FILE* fin = fopen(finname, "r");
	FILE* fout = fopen(foutname, "wb");
	if (fin == NULL || fout == NULL) {
		printf("Couldn't open input/output files. Check permissions.\n");
		return -1;
	}
	
	char line[50];
	char *mcs, *cmds, *ops;
	int mc, cmd, op, ln = 0;
	int encoded;
	while (!feof(fin)) {
		ln++;
		fgets(line, 50, fin);
		if (strcmp(line, "\n") == 0) continue;
		mcs = strtok(line, " ");
		cmds = strtok(NULL, " ");
		ops = strtok(NULL, " ");
		if (mcs == NULL || cmds == NULL || ops == NULL) {
			printf("Syntax error: line %d: %s\n", ln, line);
			return -1;
		}
		mc = atoi(mcs);
		cmd = get_command(cmds);
		if (ops[0] == '+' || ops[0] == '-') {
			if (cmd != 99) {
				printf("Syntax error: line %d: %s\nFor operands use 00-99.\n", ln, line);
				return -1;
			}
			char xbuf[7], sign = ops[0];
			ops++;
			if (strlen(ops) != 5) {
				printf("Syntax error: line %d: %s\nFor integers use format '[+/-]XXXX'.\n", ln, line);
				return -1;
			}
			sprintf(xbuf, "%c0x%s", sign, ops);
			op = strtol(xbuf, NULL, 16);
		}
		else {
			op = atoi(ops);
			if (op < 0 || op > 99) {
				printf("line %d: %s\nOperand out of bounds (00-99)\n", ln, line);
				return -1;
			}
		}

		if (cmd != 0 && cmd != 99) sc_commandEncode(cmd, op, &encoded);
		else if (cmd == 99) encoded = op;
		else {
			printf("Syntax error: no such command '%s'\n", cmds);
			return -1;
		}
		
		fwrite(&mc, sizeof(int), 1, fout);
		fwrite(&encoded, sizeof(int), 1, fout);

		mcs = cmds = ops = "";
			
	}

	fclose(fin);
	fclose(fout);
	return 0;
}
