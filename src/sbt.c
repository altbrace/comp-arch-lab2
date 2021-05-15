#define PCRE2_CODE_UNIT_WIDTH 8
#include <stdio.h>
#include <string.h>
#include <pcre2.h>

int parse(char *str) {

	if (str == NULL) return -1;
	
	pcre2_code *re;
	int errcode;
	PCRE2_SIZE erroff;
	PCRE2_UCHAR8 buffer[128];

	int rc;
	PCRE2_SIZE *ovector;
	const char **patterns = {
		"^[1-9]+0+ +REM +(\w+ *)+$",
		"^[1-9]+0+ +INPUT +[A-Z]+ *$",
		"^[1-9]+0+ +LET +[A-Z]+ += +(([A-Z]+ +[+\-*/] +[A-Z]+)|([A-Z]+)|(\d+))$",
		"^[1-9]+0+ +IF +[A-Z]+ +(([<>]=?)|(={2})) +((\d+)|([A-Z]+)) +GOTO +[1-9]+0+$",  //доделать это
	};
	size
	char msgbuf[100];

	for (int i = 0; i < 7; i++) {
		
		reti = regcomp(&regex, "^[1-9]+0+ +REM +(\w+ *)+\n+$")
	}
}
int main(int argc, char** argv) {
	
	char *finname, *foutname;

	if (argc == 2) {
		finname = argv[1];
		foutname = "output.sa";
	}
	else if (argc == 3) {
		finname = argv[1];
		foutname = argv[2];
	}
	else {
		printf("Usage: ./sbc [.sb file] [.sa file](optional)\n");
		return -1;
	}

	FILE *fin, *fout;
	fin = fopen(finname, "r");
	fout = fopen(foutname, "w");

	if (fout == NULL || fin == NULL) {
		printf("Could not open input/output files. Check permissions.\n");
		return -1;
	}
	
	char line[50];
	char *lns, *cmds, *

}
