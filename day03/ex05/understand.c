#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

struct s_node *find(struct s_node **child, char c);

void printTrie(struct s_node *node, char *buffer, int i)
{
	if (node->c)
		buffer[i++] = node->c;
	if (node->isWord)
	{
		buffer[i] = 0;
		printf("%s\n", buffer);
	}
	if (node->child)
		for (int j = 0; node->child[j]; j++)
			printTrie(node->child[j], buffer, i);
}

void printWord(struct s_node *node, char *word)
{
	if (!*word || !node)
	{
		printf("\n");
		return;
	}
	node = find(node->child, *word);
	printf("%c", *word);
	printWord(node, word + 1);
}

size_t size(struct s_node **child)
{
	size_t n = 0;
	for (int i = 0; child[i]; i++)
		n++;
	return n;
}

struct s_node *find(struct s_node **child, char c)
{
	for (int i = 0; child[i]; i++)
		if (child[i]->c == c)
			return child[i];
	return NULL;
}

struct s_node *create(char c, int isWord)
{
	struct s_node *node = malloc(sizeof(struct s_node));
	node->c = c;
	node->isWord = isWord;
	node->child = NULL;
	return node;
}

void addWord(struct s_node *node, char *word)
{
	if (!word || !*word)
		return;
	struct s_node *f;
	size_t s;
	if (node->child)
	{
		if (!(f = find(node->child, *word)))
		{
			s = size(node->child);
			node->child = realloc(node->child, (s + 2) * sizeof(struct s_node *));
			f = node->child[s] = create(*word, !*(word + 1));
			node->child[s + 1] = NULL;
		}
	}
	else
	{
		node->child = malloc(2 * sizeof(struct s_node *));
		f = node->child[0] = create(*word, !*(word + 1));
		node->child[1] = NULL;
	}
	if (f)
		addWord(f, word + 1);
}

struct s_trie *createTrie(char **dictionary)
{
	if (!dictionary)
		return NULL;
	struct s_trie *res = malloc(sizeof(struct s_trie));
	res->node = create(0, 0);
	for (int i = 0; dictionary[i]; i++)
		addWord(res->node, dictionary[i]);
	return res;
}

int helper(struct s_node *node, char *word, char *res)
{
	struct s_node *f;

	if (node->c)
		*res++ = node->c;
	if (!*word)
		return node->isWord;
	if (*word == '?')
	{
		if (node->child)
			for (int i = 0; node->child[i]; i++)
				if (helper(node->child[i], word + 1, res))
					return 1;
	}
	else
	{
		if (node->child && (f = find(node->child, *word)))
			return helper(f, word + 1, res);
	}
	return 0;
}

char *understand(char *word, struct s_trie *trie)
{
	if (!trie || !trie->node || !word || !*word)
		return NULL;
	char *res = malloc(50 *sizeof(char));
	memset(res, 0, 50);
	int found = helper(trie->node, word, res);
	return found ? res : strdup(word);
}