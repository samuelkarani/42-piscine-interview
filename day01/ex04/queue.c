/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:13:36 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/28 22:32:26 by smbaabu          ###   ########.fr       */
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

void enqueue(struct s_queue *queue, char *message)
{
	struct s_node *new, *oldLast;
	if (!queue)
		return;
	new = malloc(sizeof(struct s_node));
	new->message = message;
	new->next = NULL;
	oldLast = queue->last;
	queue->last = new;
	if (!queue->first)
		queue->first = new;
	else
		oldLast->next = new;
}

char *dequeue(struct s_queue *queue)
{
	struct s_node *oldFirst;

	if (!queue || !queue->first)
		return NULL;
	oldFirst = queue->first;
	queue->first = oldFirst->next;
	if (!queue->first)
		queue->last = NULL;
	return oldFirst->message;
}

char *peek(struct s_queue *queue)
{
	return queue && queue->first ? queue->first->message : NULL;
}

int isEmpty(struct s_queue *queue)
{
	return !(queue && queue->first);
}