#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include "myTerm/myTerm.h"
#include "myReadkey/rk.h"
#include "myBigChars/mbc.h"
#include "SimpleComputer/sc.h"

extern int ic, acc, halt;
int ic = 0;
int acc = 0;
int halt = 0;
uint8_t flags = 0;

void init() {

	system("resize -s 27 95");
	system("clear");
	
	bc_box(1, 1, 63, 17);
	mt_gotoXY(26, 1);
	printf(" Memory ");

	bc_box(63, 1, 94, 5);
	mt_gotoXY(72, 1);
	printf(" accumulator ");

	bc_box(63, 5, 94, 9);
	mt_gotoXY(69, 5);
	printf(" instructionCounter ");
	
	bc_box(63, 9, 94, 13);
	mt_gotoXY(72, 9);
	printf(" Operation ");

	bc_box(63, 13, 94, 17);
	mt_gotoXY(75, 13);
	printf(" Flags ");

	bc_box(1, 16, 43, 27);

	bc_box(63, 16, 94, 27);
	
	mt_gotoXY(76, 16);
	printf(" Keys ");
	
	mt_gotoXY(64, 17);
	printf("l - load");
	
	mt_gotoXY(64, 18);
	printf("s - save");
	
	mt_gotoXY(64, 19);
	printf("r - run");

	mt_gotoXY(64, 20);
	printf("t - step");

	mt_gotoXY(64, 21);
	printf("i - reset");

	mt_gotoXY(64, 22);
	printf("F5 - accumulator");

	mt_gotoXY(64, 23);
	printf("F6 - instructionCounter");

}

void mem_refresh() {
	
	mt_gotoXY(2, 2);
	char memS[100][6];
	char *str = (char*)malloc(6);
	enum colors black = black;
	enum colors white = white;
	enum colors blue = blue;
	enum colors red = red;
	
	for (int i = 0; i < MEMORY_SIZE; i++) {
		char sign;
		int rev;
		if (memA[i] < 0) {
			sign = '-';
			rev = -memA[i];
		}
		else {
			sign = '+';
			rev = memA[i];
		}
		if (rev <= 0xF) str = "000";

		else if (rev <= 0xFF) str = "00";

		else if (rev <= 0xFFF) str = "0";

		else str = "";
		
		sprintf(memS[i], "%c%s%x", sign, str, rev);
	}	

	bc_printStr(memS[ic], 2, 17, white, black);
	
	mt_gotoXY(76, 2);
	printf("      ");
	mt_gotoXY(78, 2);
	printf("         ");
	mt_gotoXY(78, 2);
	if (acc < 0) printf("-%x", acc - acc*2);
	else printf("+%x", acc);

	mt_gotoXY(76, 6);
	printf("     ");
	mt_gotoXY(78, 6);
	printf("%d", ic);
	
	mt_gotoXY(73, 14);
	if (sc_regGet(FIRST_BIT)) printf("OF ");
	if (sc_regGet(SECOND_BIT)) printf("ZD ");
	if (sc_regGet(THIRD_BIT)) printf("OB ");
	if (sc_regGet(FOURTH_BIT)) printf("NC ");
	if (sc_regGet(FIFTH_BIT)) printf("IC ");

	for (int i = 0; i < 10; i++) {
		mt_gotoXY(2, 3+i);

		for (int j = 0; j < 10; j++) {
			if ((i * 10 + j) == ic) mt_setbgcolor(green);
			printf("%s ", memS[i*10+j]);
			mt_colorreset();
		}

		printf("\n");
		
	}

}

void entrypoint() {

	CU();	
	void alrmhandler(int signo) {
		
		ic++;
		if (ic == 100) ic = 0;
		if (CU() == -1) raise(SIGUSR1);
		mem_refresh();
	}

	void sigusr1handler(int signo) {
		
		alarm(0);
	}

	struct itimerval nval, oval;
	signal(SIGALRM, alrmhandler);
	signal(SIGUSR1, sigusr1handler);

	nval.it_interval.tv_sec = 1;
	nval.it_interval.tv_usec = 0;
	nval.it_value.tv_sec = 1;
	nval.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &nval, &oval);

	int key = 0;
	rk_readkey(&key);
	if (key == KEY_enter) {
		raise(SIGUSR1);
		sc_regSet(FOURTH_BIT, 1);
		keyworker();
	}
	else entrypoint();
}

int ALU(int cmd, int op) {

	if (op < 0 || op > 99) {
		sc_regSet(THIRD_BIT, 1);
		return -1;
	}
	
	switch(cmd) {
		
		case 10: {
			int k = 0;
			scanf("%d", &k);
			if (k >= -0xFFFF && k <= 0xFFFF) memA[ic] = k;
			else sc_regSet(FIRST_BIT, 1);
			break;
		}

		case 11:
			if (memA[op] < 0) printf("-%x", -memA[op]); 
			else printf("%x", memA[op]);
			break;

		case 20:
			acc = memA[op];
			break;

		case 21:
			memA[op] = acc;
			break;

		case 30:
			acc += memA[op];
			break;

		case 31:
			acc -= memA[op];
			break;

		case 32:
			if (memA[op] == 0) {
				sc_regSet(SECOND_BIT, 1);
				break;
			}
			acc /= memA[op];
			break;

		case 33:
			acc *= memA[op];
			break;

		case 40:
			ic = op;
			break;

		case 41:
			if (acc < 0) ic = op;
			break;

		case 42:
			if (acc == 0) ic = op;
                        break;

		case 43:
			halt = 1;
			break;

		case 51:
			memA[op] = ~acc;
			break;
		case 52:
			acc &= memA[op];
			break;

		case 53:
			acc |= memA[op];
			break;

		case 54:
			acc ^= memA[op];
			break;

		case 55:
			if (acc > 0) ic = op;
                        break;
		
		case 56:
			if (sc_regGet(FIRST_BIT)) ic = op;
			break;

		case 57:
			if (!sc_regGet(FIRST_BIT)) ic = op;
                        break;
		
		case 58:
			if (acc % 2 == 0) ic = op;
			break;

		case 59:
			if (acc % 2 != 0) ic = op;
                        break;

		case 60:
			acc = memA[op] << 1; 
                        break;

		case 61:
			acc = memA[op] >> 1;
			break;

		case 62:
			acc = memA[op] << 1 | memA[op] >> (32 - 1);
			break;

		case 63:
			acc = memA[op] >> 1 | memA[op] << (32 - 1);
			break;

		case 64:
			if (memA[op] < 0) acc = ~(-memA[op]) + 1;
			else acc = memA[op];
			break;

		case 65:
			if (acc > 0 && acc < 100) acc = memA[op] + memA[acc];
			else sc_regSet(THIRD_BIT, 1);
			break;

		case 66:
			if (acc > 0 && acc < 100) acc = memA[op] - memA[acc];
                        else sc_regSet(THIRD_BIT, 1);
                        break;

		case 67:
			acc = memA[op] << acc;
			break;

		case 68:
			acc = memA[op] >> acc;
			break;

		case 69:
			acc = memA[op] << acc | memA[op] >> (32 - acc);
			break;

		case 70:
			acc = memA[op] >> acc | memA[op] << (32 - acc);
			break;

		case 71:
			if (acc > 0 && acc < 100) memA[acc] = memA[op];
			else sc_regSet(THIRD_BIT, 1);
			break;

		case 72:
			if (acc > 0 && acc < 100) memA[op] = memA[acc];
			else sc_regSet(THIRD_BIT, 1);
			break;

		case 73:
			if (memA[acc] > 0 && memA[acc] < 100) memA[memA[acc]] = memA[op];
		        else sc_regSet(THIRD_BIT, 1);
			break;

		case 74:
			if (memA[acc] > 0 && memA[acc] < 100) memA[op] = memA[memA[acc]];
			else sc_regSet(THIRD_BIT, 1);
			break;

		case 75:
			if (memA[acc] > 0 && memA[acc] < 100) acc = memA[op] + memA[memA[acc]];
			else sc_regSet(THIRD_BIT, 1);
			break;

		case 76:
			if (memA[acc] > 0 && memA[acc] < 100) acc = memA[op] - memA[memA[acc]];
                        else sc_regSet(THIRD_BIT, 1);
                        break;

	}

	mem_refresh();
	return 0;

}

void mem_load_sat(char* filename) {
	
	FILE* fin = fopen(filename, "rb");
	if (fin == NULL) {
		printf("Couldn't read from file '%s'\n", filename);
		return;
	}

	int mc;

	while (!feof(fin)) {
		
		fread(&mc, sizeof(int), 1, fin);
		fread(&memA[mc], sizeof(int), 1, fin);
	}

	fclose(fin);
	mem_refresh();
}

int CU() {

	uint16_t value = memA[ic];
	int ins = 0, op = 0;
	if (sc_commandDecode(value, &ins, &op) != 0) return 0;
	if (ins == 43) return -1;
	
	ALU(ins, op);
	return 0;

}
void keyworker() {
	

	int key = 0;
	
	while (1) {
		mt_gotoXY(2, 27);
		rk_readkey(&key);

		if (key == KEY_down && ic <= 89) ic += 10;

		else if ((key == KEY_right) && (ic <= 98)) ic += 1;

		else if ((key == KEY_up) && (ic >= 10)) ic -= 10; 

		else if ((key == KEY_left) && (ic >= 1)) ic -= 1;

		else if (key == KEY_l) sc_memoryLoad("memDB");

		else if (key == KEY_s) sc_memorySave("memDB");

		else if (key == KEY_i) sc_memoryReset();

		else if (key == KEY_f5) acc = memA[ic];

		else if (key == KEY_f6) {
			int k = 0;
			scanf("%d", &k);
			if ((k >= 0) && (k <= 100)) ic = k;
		}
			
		mem_refresh();

		
	}
}


int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: ./sc [.o binary file]\n");
		return -1;
	}
	init();
//	memA[5] = 0xF;
//	memA[10] = 0xA2;
//	memA[18] = 0x33;
//	memA[3] = 0xFB;
//	memA[88] = 0xFFFF;
//	memA[98] = 12;
//	memA[99] = -12;
	mem_load_sat(argv[1]);
	
	entrypoint();	
//	scanf("%d");
	return 0;
}
