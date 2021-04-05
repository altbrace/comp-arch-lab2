#include <stdlib.h>
#include "myTerm/myTerm.h"
#include "myReadkey/rk.h"
#include "myBigChars/mbc.h"
#include "SimpleComputer/sc.h"

void init() {

	system("resize -s %d %d", 27, 95);
	
	bc_box(0, 0, 51, 11);
	mt_gotoXY(0, 52);

	bc_box()
}
void mem_refresh()  
