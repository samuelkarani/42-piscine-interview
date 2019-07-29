/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimumMoves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 21:17:59 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/28 23:43:54 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"

struct s_queue *init(void)
{
	struct s_queue *queue = malloc(sizeof(struct s_queue));
	queue->first = queue->last = NULL;
	return queue;
}

void enqueue(struct s_queue *queue, struct s_node *node, int moves)
{
	struct s_item *oldLast, *new;
	if (!queue || !node)
		return;
	new = malloc(sizeof(struct s_item));
	new->node = node;
	new->next = NULL;
	oldLast = queue->last;
	queue->last = new;
	if (!queue->first)
		queue->first = new;
	else
		oldLast->next = new;
	node->value = moves;
}

struct s_node *dequeue(struct s_queue *queue)
{
	struct s_item *oldFirst;
	if (!queue || !queue->first)
		return NULL;
	oldFirst = queue->first;
	queue->first = oldFirst->next;
	if (!queue->first)
		queue->last = NULL;
	return oldFirst->node;
}

int isEmpty(struct s_queue *queue)
{
	return !(queue && queue->first);
}

int minimumMoves(struct s_node *begin)
{
	struct s_queue *queue;
	struct s_node *node;

	if (!begin)
		return -1;
	queue = init();
	enqueue(queue, begin, 0);
	while (!isEmpty(queue))
	{
		node = dequeue(queue);
		if (node->isFinal)
			return node->value;
		if (node->next)
			enqueue(queue, node->next, node->value + 1);
		if (node->random && node->random != node)
			enqueue(queue, node->random, node->value + 1);
	}
	return -1;
}