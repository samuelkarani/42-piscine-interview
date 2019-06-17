#include <stdio.h>  //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...

#include "header.h"

int main(void)
{

	/*-------------------
	launch your test here
	--------------------*/
	struct s_queue *q;
	q = queueInit();
	printf("isempty %d\n", isEmpty(q));
	enqueue(q, "a");
	printf("added a - isempty %d\n", isEmpty(q));
	enqueue(q, "b");
	printf("added b - isempty %d\n", isEmpty(q));
	enqueue(q, "c");
	printf("added c - isempty %d\n", isEmpty(q));

	printf("peek %s dequeue %s isempty %d\n", peek(q), dequeue(q), isEmpty(q));
	printf("peek %s dequeue %s isempty %d\n", peek(q), dequeue(q), isEmpty(q));
	printf("peek %s dequeue %s isempty %d\n", peek(q), dequeue(q), isEmpty(q));

	printf("\n");
	q = queueInit();
	printf("isempty %d\n", isEmpty(q));
	enqueue(q, "a");
	printf("added a - isempty %d\n", isEmpty(q));
	printf("peek %s dequeue %s isempty %d\n", peek(q), dequeue(q), isEmpty(q));
	printf("peek %s dequeue %s isempty %d\n", peek(q), dequeue(q), isEmpty(q));
	printf("isempty %d\n", isEmpty(q));

	return (0);
}

// Function used for the test
// Don't go further :)
