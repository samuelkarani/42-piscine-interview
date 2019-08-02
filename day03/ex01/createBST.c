#include <stdlib.h>
#include "header.h"

struct s_node *create(int n)
{
	struct s_node *res = malloc(sizeof(struct s_node));
	res->value = n;
	res->left = res->right = NULL;
	return res;
}

struct s_node *createBST(int *arr, int n)
{
	if (n <= 0 || !arr)
		return 0;
	int mid = n / 2;
	struct s_node *node = create(arr[mid]);
	node->left = createBST(arr, mid);
	node->right = createBST(arr + mid + 1, n - mid - 1);
	return node;
}