#include "header.h"

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

void saveTheSequoia(struct s_node **root)
{
	if (!root || !*root)
		return;
	struct s_node *largest; int l;
	largest = *root;
	saveTheSequoia(&(*root)->left);
	saveTheSequoia(&(*root)->right);
	if ((*root)->left && (*root)->left->value > largest->value)
		largest = (*root)->left;
	if ((*root)->right && (*root)->right->value > largest->value)
		largest = (*root)->right;
	if (largest != *root)
	{
		swap(root, largest, l = largest == (*root)->left);
		saveTheSequoia(l ? &(*root)->left : &(*root)->right);
	}
}
