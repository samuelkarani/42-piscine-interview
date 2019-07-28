/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatWasThat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 00:36:10 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/28 02:22:50 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "header.h"

static int min(int a, int b)
{
	if (a == -1 && b == -1)
		return -1;
	if (a == -1)
		return b;
	if (b == -1)
		return a;
	return a < b ? a : b;
}

char    *delete(char *word, int pos)
{
	int i, l, idx;
	char *res;

	l = strlen(word);
	res = malloc(l);
	i = idx = 0;
	while (i < l)
	{
		if (i != pos)
			res[idx++] = word[i];
		i++;
	}
	res[idx] = 0;
	return res;
}

char    *replace(char *word, int pos, char c)
{
	char *res = strdup(word);
	res[pos] = c;
	return res;
}

char    *add(char *word, int pos, char c)
{
	int l, idx, i;
	char *res;

	l = strlen(word);
	res = malloc(l + 1 + 1);
	i = idx = 0;
	while (i < l)
	{
		if (i == pos)
			res[idx++] = c;
		res[idx++] = word[i++];
	}
	res[idx] = 0;
	return res;
}

int check(char *word, char *dWord, int depth)
{
	int i, lw, ld;
	char *a, *b;

	i = 0;
	while (word[i] && dWord[i] && word[i] == dWord[i])
		i++;
	if (!word[i] && !dWord[i])
		return depth;
	if (depth == DEPTH || !word[i] || !dWord[i])
		return -1;
	lw = strlen(word + i), ld = strlen(dWord + i);
	a = NULL;
	if (lw > ld)
		a = delete(word, i);
	else if (lw < ld)
		a = add(word, i, dWord[i]);
	b = replace(word, i, dWord[i]);
	if (a)
		return min(check(a, dWord, depth + 1), check(b, dWord, depth + 1));
	return check(b, dWord, depth + 1);
}

char	*whatWasThat(char *word, char **dict)
{
	char *res;
	int c, smallest;

	res = NULL;
	smallest = INT_MAX;
	for (int i = 0; dict[i]; i++)
	{
		c = check(word, dict[i], 0);
		if (c != -1 && c < smallest)
		{
			smallest = c;
			res = dict[i];
		}
	}
	return res;
}