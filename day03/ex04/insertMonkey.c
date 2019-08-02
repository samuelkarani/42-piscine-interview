#include <stdlib.h>
#include "header.h"

struct s_queue *queueInit(void)
{
	struct s_queue *queue = malloc(sizeof(struct s_queue));
	queue->first = queue->last = NULL;
	return queue;
}

void enqueue(struct s_queue *queue, struct s_node *node)
{
	struct s_item *new, *oldLast;
	if (!queue)
		return;
	new = malloc(sizeof(struct s_item));
	new->node = node;
	new->next = NULL;
	oldLast = queue->last;
	queue->last = new;
	if (!queue->first)
		queue->first = new;
	else
		oldLast->next = new;
}

struct s_node *dequeue(struct s_queue *queue)
{
	struct s_node *res;
	if (!queue || !queue->first)
		return NULL;
	res = queue->first->node;
	queue->first = queue->first->next;
	if (!queue->first)
		queue->last = NULL;
	return res;
}

int isEmpty(struct s_queue *queue)
{
	return !(queue && queue->first);
}

int count(struct s_node *node)
{
	if (!node)
		return 0;
	return 1 + count(node->left) + count(node->right);
}

struct s_node *getNode(struct s_node *node, int idx)
{
	struct s_queue *queue;
	queue = queueInit();
	enqueue(queue, node);
	while (!isEmpty(queue) && idx >= 0)
	{
		node = dequeue(queue);
		if (node->left)
			enqueue(queue, node->left);
		if (node->right)
			enqueue(queue, node->right);
		idx--;
	}
	return node;
}

void insertNode(struct s_node *root, struct s_node *monkey)
{
	int c;
	c = count(root);
	root = getNode(root, c / 2);
	if (root->left)
		root->right = monkey;
	else
		root->left = monkey;
}

void swap(struct s_node **oldRoot, struct s_node *newRoot, int isLeft)
{
	struct s_node *left, *right, *node;
	left = newRoot->left, right = newRoot->right,
		node = isLeft ? (*oldRoot)->right : (*oldRoot)->left;
	if (isLeft)
	{
		newRoot->left = *oldRoot;
		newRoot->right = node;
	}
	else
	{
		newRoot->right = *oldRoot;
		newRoot->left = node;
	}
	(*oldRoot)->left = left;
	(*oldRoot)->right = right;
	*oldRoot = newRoot;
}

void heapify(struct s_node **root)
{
	if (!root || !*root)
		return;
	struct s_node *largest; int l;
	largest = *root;
	heapify(&(*root)->left);
	heapify(&(*root)->right);
	if ((*root)->left && (*root)->left->value > largest->value)
		largest = (*root)->left;
	if ((*root)->right && (*root)->right->value > largest->value)
		largest = (*root)->right;
	if (largest != *root)
	{
		swap(root, largest, l = largest == (*root)->left);
		heapify(l ? &(*root)->left : &(*root)->right);
	}
}

void insertMonkey(struct s_node **root, struct s_node *monkey)
{
	if (!root || !monkey)
		return;
	if (!*root)
	{
		*root = monkey;
		return;
	}
	insertNode(*root, monkey);
	heapify(root);
}