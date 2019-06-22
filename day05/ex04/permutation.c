/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:46:10 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/19 20:04:11 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

char *strjoin(char *a, char *b)
{
	int alen, blen;
	char *res = malloc((alen = strlen(a)) + (blen = strlen(b)) + 1);
	strncpy(res, a, alen);
	strncpy(res + alen, b, blen);
	return res;
}

char *rest(char *s, int i)
{
	int l;
	if ((l = strlen(s)) == 1)
		return strdup("");
	char *res = malloc(l);
	strncpy(res, s, i);
	memmove(res + i, s + i + 1, l - i - 1);
	return res;
}

char *create(char c)
{
	char *res;
	asprintf(&res, "%c", c);
	return res;
}

void helper(char *cur, char *rst)
{
	int l;
	if (!(l = strlen(rst)))
		printf("%s\n", cur);
	int i = -1;
	while (++i < l)
		helper(strjoin(cur, create(rst[i])), rest(rst, i));
}

void printPermutations(char *str)
{
	helper(strdup(""), strdup(str));
}