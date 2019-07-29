/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copyGameBoard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 17:32:12 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/28 16:43:02 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"

struct s_node *create(int value)
{
	struct s_node *res = malloc(sizeof(struct s_node));
	res->value = value;
	res->next = res->random = NULL;
	return res;
}

int find_idx(struct s_node *haystack, struct s_node *needle)
{
	int idx;

	idx = 0;
	while (haystack != needle)
	{
		haystack = haystack->next;
		idx++;
	}
	return idx;
}

struct s_node *find(struct s_node *node, int idx)
{
	while (idx-- > 0)
		node = node->next;
	return node;
}

struct s_node *cloneGameBoard(struct s_node *node)
{
	struct s_node *res, *r, *n;

	if (!node)
		return NULL;
	n = node;
	r = res = create(node->value);
	while ((node = node->next))
	{
		res->next = create(node->value);
		res = res->next;
	}
	node = n;
	res = r;
	while (node)
	{
		if (node->random)
			res->random = find(r, find_idx(n, node->random));
		node = node->next;
		res = res->next;
	}
	return r;
}