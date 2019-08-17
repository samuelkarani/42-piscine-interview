/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neverForget.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 19:44:00 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/17 11:29:53 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int sizeList(struct s_word *words)
{
	int i = 0;
	while (words)
	{
		words = words->next;
		i++;
	}
	return i;
}

int numWords(char **dictionary)
{
	int i = 0;
	for (i = 0; dictionary[i]; i++)
		;
	return i;
}

int cmp(const void *a, const void *b)
{
	char **s = (char **)a;
	char **r = (char **)b;
	int x = strlen((char *)*s), y = strlen((char *)*r);
	if (x < y)
		return -1;
	if (x == y)
		return 0;
	return 1;
}

int findIndex(struct s_word *dict, int len)
{
	for (int i = 0; dict; dict = dict->next, i++)
	{
		if (dict->len == len)
			return i;
	}
	return -1;
}

void fsort(struct s_word *words)
{
	struct s_word *i, *j;
	int tlen;
	char *tword;

	for (i = words; i->next; i = i->next)
	{
		for (j = words; j->next; j = j->next)
		{
			if (j->len > j->next->len)
			{
				tword = j->word;
				tlen = j->len;
				j->word = j->next->word;
				j->len = j->next->len;
				j->next->word = tword;
				j->next->len = tlen;
			}
		}
	}
}

struct s_word *createWord(char *word)
{
	struct s_word *wordNode = malloc(sizeof(struct s_word));
	wordNode->word = word;
	wordNode->modified = NULL;
	wordNode->index = -1;
	wordNode->len = strlen(word);
	return wordNode;
}

char *fstrsub(char *s, int start, int len)
{
	char *res = malloc((len + 1) * sizeof(char));
	memcpy(res, s + start, len);
	res[len] = 0;
	return res;
}

int isValid(char *words)
{
	char c;

	for (int i = 0; (c = words[i]); i++)
		if (!isalpha(c) && !isspace(c))
			return 0;
	return 1;
}

struct s_word *parse(char *words)
{
	struct s_word *startNode, *node;
	char *s;
	int i, start, end;

	startNode = node = NULL;
	i = start = 0;
	for (int i = 0; words[i]; i++)
	{
		if (!isspace(words[i]) && i > 0 && isspace(words[i - 1]))
			start = i;
		else if ((isspace(words[i]) && i > 0 && !isspace(words[i - 1]))
			|| (!words[i + 1] && !isspace(words[i])))
		{
			end = !words[i + 1];
			s = fstrsub(words, start, i - start + end);
			if (!node)
				startNode = node = createWord(s);
			else
			{
				node->next = createWord(s);
				node = node->next;
			}
		}
	}
	return startNode;
}

void printAlpha(char *alphabet)
{
	for (int i = 0; i < 127; i++)
		if (alphabet[i])
			printf("%c vs %c\n", (char)i, alphabet[i]);
}

char *neverForget(char *words, char **dictionary)
{
	struct s_word *wordNode, *node, *dictList;
	char *r;
	char alphabet[127] = {0};

	if (!words || !dictionary || !dictionary[0] || !isValid(words))
		return NULL;

	wordNode = parse(words);

	if (!words)
		return NULL;

	fsort(wordNode);
	mergesort(dictionary, numWords(dictionary), sizeof(char *), &cmp);

	dictList = node = createWord(dictionary[0]);
	for (int i = 1; dictionary[i]; i++)
	{
		node->next = createWord(dictionary[i]);
		node = node->next;
	}

	int n, index, a, c, fail, k;
	n = sizeList(wordNode);
	char *stack[n]; int si = 0;

	node = wordNode;
	a = 0, si = 0;
	while (wordNode)
	{
		fail = 0;
		if (wordNode->index == -1)
		{
			index = findIndex(dictList, wordNode->len);
			if (index == -1)
				return NULL;
			wordNode->index = index;
		}
		else
		{
			if ((int)strlen(dictionary[wordNode->index + 1]) > wordNode->len)
				fail = 1;
			wordNode->index++;
		}

		if (fail)
			r = NULL;
		else
			r = dictionary[wordNode->index];
		printf("%s %s\n", wordNode->word, r);

		if (!fail)
		{
			k = 0;
			for (int i = 0; (c = wordNode->word[i]); i++)
			{
				if (alphabet[(int)r[i]])
				{
					fail = 1;
					break ;
				}
				if (!alphabet[c])
				{
					alphabet[c] = r[i];
					a++;
					k++;
				}
			}
		}
		if (fail)
		{
			if (!r)
				r = stack[--si];
			for (int i = 0; (c = r[i]) && i < k; i++)
			{
				alphabet[c] = 0;
				a--;
			}
			wordNode = node;
			continue ;
		}
		stack[si++] = r;
		wordNode->modified = r;
		wordNode = wordNode->next;
		if (a == 26)
			break ;
	}

	printAlpha(alphabet);
	return NULL;
}