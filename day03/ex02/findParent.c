#include <stdlib.h>
#include <string.h>
#include "header.h"

int  contains(struct s_node *root, char *s)
{
	if (!root) 	return 0;
	if (!strcmp(root->name, s))
		return 1;
	for (int i = 0; root->children[i]; i++)
		if (contains(root->children[i], s))
			return 1;
	return 0;
}


struct s_node *search(struct s_node *root, char *firstSpecies, char *secondSpecies)
{
	if (!root)
		return NULL;
	if (!strcmp(root->name, firstSpecies) || !strcmp(root->name, secondSpecies))
		return root;
	struct s_node *node, *prev = NULL;
	for (int i = 0; root->children[i]; i++)
	{
		node = search(root->children[i], firstSpecies, secondSpecies);
		if (node && prev)
			return root;
		if (node)
			prev = node;
	}
	return prev;
}



struct s_node *findParent(struct s_node *root, char *firstSpecies, char *secondSpecies)
{
	if (!(contains(root, firstSpecies)  && contains(root, secondSpecies)))
		return NULL;
	return search(root, firstSpecies, secondSpecies);
}