/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:46:10 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/04 16:53:03 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

char *rest(char *s, int i)
{
	char *res = strdup(s);
	memmove(res + i, s + i + 1, strlen(s) - i - 1);
	return res;
}

void helper(char *cur, int idx, char *rst, int n)
{
	if (idx == n)
		printf("%s\n", cur);
	for (int i = 0; i < n - idx; i++)
	{
		cur[idx] = rst[i];
		char *nrst = rest(rst, i);
		helper(cur, idx + 1, nrst, n);
	}
}

void printPermutations(char *str)
{
	if (str)
		helper(strdup(str), 0, str, strlen(str));
}