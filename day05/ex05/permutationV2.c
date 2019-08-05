/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutationV2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 22:58:51 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/04 16:53:44 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

int factorial(int f)
{
    if (f == 0) return 1;
    return f * factorial(f - 1);
}

char *rest(char *s, int i)
{
	char *res = strdup(s);
	memmove(res + i, s + i + 1, strlen(s) - i - 1);
	return res;
}

void helper(char *cur, int idx, char *rst, int n, struct s_dict *dict)
{
	if (idx == n && dictSearch(dict, cur) == -1)
	{
		printf("%s\n", cur);
		dictInsert(dict, cur, 1);
	}
	for (int i = 0; i < n - idx; i++)
	{
		cur[idx] = rst[i];
		char *nrst = rest(rst, i);
		helper(cur, idx + 1, nrst, n, dict);
	}
}

void	printUniquePermutations(char *str)
{
    if (str)
		helper(strdup(str), 0, str, strlen(str), dictInit(factorial(strlen(str))));
}
