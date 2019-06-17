#include <stdio.h>  //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...

#include "header.h"

int main(void)
{
	struct s_tank *tank = initTank();

	/*-------------------
	launch your test here
	--------------------*/
	printTank(tank);
	printf("add 990\n");
	tankPush(tank, 990);
	printTank(tank);
	printf("add 100\n");
	tankPush(tank, 100);
	printTank(tank);
	printf("add 10\n");
	tankPush(tank, 10);
	printTank(tank);
	printf("popped: %d\n", tankPop(tank));
	printTank(tank);
	printf("popped: %d\n", tankPop(tank));
	printTank(tank);
	printf("add 200\n");
	tankPush(tank, 200);
	printTank(tank);
	printf("popped: %d\n", tankPop(tank));
	printTank(tank);
	printf("popped: %d\n", tankPop(tank));
	printTank(tank);
	printf("popped: %d\n", tankPop(tank));
	printTank(tank);
	return (0);
}

// Function used for the test
// Don't go further :)
