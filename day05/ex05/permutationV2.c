/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutationV2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 22:58:51 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/19 23:13:50 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

unsigned long factorial(unsigned long f)
{
    if (f == 0 ) 
        return 1;
    return(f * factorial(f - 1));
}

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

void helper(char *cur, char *rst, struct s_dict *dict)
{
	int l;
	if (!(l = strlen(rst)))
    {
        if (dictSearch(dict, cur) == -1)
            dictInsert(dict, cur, strlen(cur));
    }
	int i = -1;
	while (++i < l)
		helper(strjoin(cur, create(rst[i])), rest(rst, i), dict);
}


void	printUniquePermutations(char *str)
{
    struct s_dict *dict = dictInit(factorial(strlen(str)));
    helper(strdup(""), strdup(str), dict);
    struct s_item **items = dict->items;
    struct s_item *item;
    int i = -1;
    while (++i < dict->capacity)
    {
        if ((item = items[i]))
        {
            while (item)
            {
                printf("%s\n", items[i]->key);
                item = item->next;
            }
        }
    }
}
