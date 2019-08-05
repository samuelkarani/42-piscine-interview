/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimumMoves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 20:15:00 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/05 01:11:42 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "header.h"

struct s_node *create(struct s_node *node, int value)
{
	struct s_node *res = memcpy(malloc(sizeof(struct s_node)), node, sizeof(struct s_node));
	res->value = value;
	return res;
}

int minimumMoves(struct s_node *begin)
{
	if (!begin)
		return -1;
	struct s_queue *queue = queueInit();
	enqueue(queue, create(begin, 0));
	while (queue->first)
	{
		struct s_node *node = dequeue(queue);
		if (node->isFinal)
			return node->value;
		if (node->next)
			enqueue(queue, create(node->next, node->value + 1));
		if (node->random && node->random != node)
			enqueue(queue, create(node->random, node->value + 1));
	}
	return -1;
}