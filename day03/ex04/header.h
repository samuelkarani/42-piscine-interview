#ifndef HEADER_H
# define HEADER_H

/*--------------------------------
  !! required structure
  --------------------------------*/
struct s_node {
	int value;
	struct s_node *right;
	struct s_node *left;
};


/*--------------------------------
  :) function you must implement
  --------------------------------*/
void insertMonkey(struct s_node **root, struct s_node *monkey);


/*--------------------------------
  ?? test function used in main
  --------------------------------*/
struct s_node *genMaxHeap(unsigned seed);
void printBinaryTree(struct s_node *t);
struct s_node *randomMonkey(void);


/*--------------------------------
  &  your own other function
  --------------------------------*/

struct s_item {
	struct s_node *node;
	struct s_item *next;
};

struct s_queue {
  struct s_item *first;
	struct s_item *last;
};


struct s_queue *queueInit(void);

struct s_node *dequeue(struct s_queue *queue);

void enqueue(struct s_queue *queue, struct s_node *item);

int isEmpty(struct s_queue *queue);
#endif
