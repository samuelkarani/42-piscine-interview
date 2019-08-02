#include "header.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int mn(int a, int b)
{
	return a < b ? a : b;
}

int mx(int a, int b)
{
	return a > b ? a : b;
}

int min(struct s_node *root, int smallest)
{
	if (!root)
		return smallest;
	if (root->value < smallest)
		smallest = root->value;
	return mn(min(root->left, smallest), min(root->right, smallest));
}

int max(struct s_node *root, int largest)
{
	if (!root)
		return largest;
	if (root->value > largest)
		largest = root->value;
	return mx(max(root->left, largest), max(root->right, largest));
}

int count(struct s_node *root)
{
	if (!root)
		return 0;
	return 1 + count(root->left) + count(root->right);
}

int height(struct s_node *root)
{
	if (!root)
		return -1;
	return 1 + mx(height(root->left), height(root->right));
}

int isBST(struct s_node *root)
{
	if (!root)
		return 1;
	if (!isBST(root->left) || !isBST(root->right))
		return 0;
	int a = root->left ? root->left->value : INT_MIN;
	int b = root->right ? root->right->value : INT_MAX;
	return a <= root->value && root->value < b;
}

int isBalanced(struct s_node *root)
{
	if (!root)
		return 1;
	if (!isBalanced(root->left) || !isBalanced(root->right))
		return 0;
	return abs(height(root->left) - height(root->right)) <= 1;
}

struct s_info   getInfo(struct s_node *root)
{
	struct s_info res;
	memset(&res, 0, sizeof(struct s_info));
	res.min = min(root, INT_MAX);
	res.max = max(root, INT_MIN);
	res.elements = count(root);
	res.height = height(root);
	res.isBST = isBST(root);
	res.isBalanced = isBalanced(root);
	return res;
}