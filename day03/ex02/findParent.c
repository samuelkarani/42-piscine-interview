#include <stdlib.h>
#include <string.h>
#include "header.h"

struct s_node *findParent(struct s_node *root, char *firstSpecies, char *secondSpecies)
{
	if (!root)
		return NULL;
	if (!strcmp(root->name, firstSpecies) || !strcmp(root->name, secondSpecies))
		return root;
	struct s_node *node, *res = NULL;
	for (int i = 0; root->children[i]; i++)
	{
		node = findParent(root->children[i], firstSpecies, secondSpecies);
		if (node && res)
			return root;
		if (node)
		{
			if (strcmp(node->name, firstSpecies) && strcmp(node->name, secondSpecies))
				return node;
			res = node;
		}
	}
	return res;
}