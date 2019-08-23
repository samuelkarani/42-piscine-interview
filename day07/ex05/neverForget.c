/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neverForget.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 19:44:00 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/21 15:55:36 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

struct s_word *createWord(char *word)
{
	struct s_word *wordNode = malloc(sizeof(struct s_word));
	wordNode->word = word;
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

int numWords(char **dictionary)
{
	int i = 0;
	for (i = 0; dictionary[i]; i++)
		;
	return i;
}

int cmp_len(const void *a, const void *b)
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

int cmp_alpha(const void *a, const void *b)
{
	char **s = (char **)a;
	char **r = (char **)b;
	return strcmp((char *)*s, (char *)*r);
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

void printWords(char **words, int n)
{
	for (int i = 0; i < n; i++)
		printf("%s\n", words[i]);
}

void printAlpha(char *alphabet)
{
	for (int i = 0; i < 127; i++)
		if (alphabet[i])
			printf("%c = %c, ", (char)i, alphabet[i]);
}

void undoAlpha(char *alphabet, char *unique, char *from, int n)
{
	for (int i = 0;i < n; i++)
	{
		if (alphabet[(int)unique[i]] && from[i] == '?')
			alphabet[(int)unique[i]] = 0;
	}
}

int setAlpha(char *alphabet, char *unique, char *to, char *from)
{
	int n = 0;
	for (int i = 0; unique[i]; i++)
	{
		if (from[i] == '?')
		{
			if (alphabet[(int)unique[i]])
			{
				// printf("failed to set %c = %c\n", unique[i], alphabet[(int)unique[i]]);
				undoAlpha(alphabet, unique, from, i);
				return 0;
			}
			else
			{
				alphabet[(int)unique[i]] = to[i];
				n++;
			}
		}
	}
	return n;
}

char *modify(char *word, char *alphabet)
{
	char *res = strdup(word);
	for (int i = 0; res[i]; i++)
	{
		if (alphabet[(int)res[i]])
			res[i] = alphabet[(int)res[i]];
		else
			res[i] = '?';
	}
	return res;
}

int find(char **dictionary, int w, int len)
{
	int start, end, mid, l;

	start = 0, end = w - 1;
	while (start < end)
	{
		mid = (start + end) / 2;
		l = strlen(dictionary[mid]);
		if (l == len)
			return mid;
		if (len > l)
			start = mid + 1;
		else
			end = mid - 1;
	}
	return -1;
}

int contains(char *word, char *dictWord)
{
	for (int i = 0; word[i]; i++)
		if (word[i] != '?' && word[i] != dictWord[i])
			return 0;
	return 1;
}

int getPossible(char *word, char **dictionary, int w, char **buffer)
{
	int f, i, l, idx;

	f = find(dictionary, w, strlen(word));
	l = strlen(word);
	idx = 0;
	i = f;
	while ((int)strlen(dictionary[i]) == l)
	{
		if (contains(word, dictionary[i]))
			buffer[idx++] = dictionary[i];
		i--;
	}
	i = f;
	while ((int)strlen(dictionary[i]) == l)
	{
		if (contains(word, dictionary[i]))
			buffer[idx++] = dictionary[i];
		i++;
	}
	return idx;
}

int getUnique(struct s_word *node, char **buffer)
{
	struct s_word *prev = NULL;
	int idx = 0;
	while (node)
	{
		if (idx == 0 || strlen(node->word) > strlen(prev->word))
			buffer[idx++] = node->word;
		prev = node;
		node = node->next;
	}
	return idx;
}

int helper(char **uniqueWords, int n, char **dictionary, int w, char *alphabet, int index)
{
	char *from, *to;
	int p;

	if (index == n)
		return 1;
	char *buffer[w];
	from = modify(uniqueWords[index], alphabet);
	p = getPossible(from, dictionary, w, buffer);
	// printWords(buffer, p);
	// printAlpha(alphabet);
	// printf("possible %d for %s\n", p, uniqueWords[index]);
	for (int i = 0; i < p; i++)
	{
		to = buffer[i];
		// printf("%d: %s = %s from %s\n", i, uniqueWords[index], to, from);
		if (!setAlpha(alphabet, uniqueWords[index], to, from))
			continue ;
		// printf("\n");
		if (helper(uniqueWords, n, dictionary, w, alphabet, index + 1))
			return 1;
		else
		{
			// printf("backtracking...\n");
			undoAlpha(alphabet, uniqueWords[index], from, strlen(uniqueWords[index]));
		}
	}
	return 0;
}

char *neverForget(char *words, char **dictionary)
{
	struct s_word *node;
	char alphabet[127] = {0};
	int found, n, w;

	if (!words || !dictionary || !dictionary[0] || !isValid(words) || !(node = parse(words)))
		return NULL;

	fsort(node);
	mergesort(dictionary, w = numWords(dictionary), sizeof(char *), &cmp_len);

	n = sizeList(node);
	char *uniqueWords[n];
	n = getUnique(node, uniqueWords);
	// printWords(uniqueWords, n);
	found = helper(uniqueWords, n, dictionary, w, alphabet, 0);
	return NULL;
}