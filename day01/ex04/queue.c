/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:13:36 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/13 22:22:21 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"

struct s_queue *queueInit(void)
{
	struct s_queue *q = malloc(sizeof(struct s_queue));
	q->first = NULL;
	q->last = NULL;
	return q;
}

char *dequeue(struct s_queue *queue)
{
	struct s_node *p;
	if (!queue || !queue->first)
		return NULL;
	p = queue->first;
	queue->first = p->next;
	if (queue->last == p)
		queue->last = NULL;
	return p->message;
}

void enqueue(struct s_queue *queue, char *message)
{
	struct s_node *new, *p;
	if (!queue)
		return;
	new = malloc(sizeof(struct s_node));
	new->message = message;
	new->next = NULL;
	if (!queue->first && !queue->last)
	{
		queue->first = new;
		queue->last = new;
	}
	else
	{
		p = queue->last;
		queue->last = new;
		p->next = new;
	}
}

char *peek(struct s_queue *queue)
{
	if (!queue || !queue->first)
		return NULL;
	return queue->first->message;
}

int isEmpty(struct s_queue *queue)
{
	return !(queue && queue->first);
}