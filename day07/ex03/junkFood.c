/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junkFood.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:01:11 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/15 19:30:06 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

int sizeQueue(struct s_queue *queue)
{
	struct s_queueItem *node;
	int i;

	node = queue->first;
	i = 0;
	while (node)
	{
		node = node->next;
		i++;
	}
	return i;
}

struct s_node *startNode(struct s_graph *graph, char *youAreHere)
{
    struct s_node *place, *start;
    start = NULL;

    for (int i = 0; (place = graph->places[i]); i++)
        if (!strcmp(place->name, youAreHere))
            start = place;
    return start;
}

struct s_sellers *closestSellers(struct s_graph *graph, char *youAreHere)
{
	struct s_queue *queue, *qSellers;
	struct s_sellers *sellers;
	struct s_node *node, *neighbor;
    int n, idx, depth, c, prev;

	node = startNode(graph, youAreHere);
	if (!node)
		return NULL;
	queue = queueInit(), qSellers = queueInit();
	enqueue(queue, node);
	node->visited = 1;
	c = 1, depth = 0, prev = 0;
	while (!isEmpty(queue))
	{
		node = dequeue(queue);
		for (int i = 0; (neighbor = node->connectedPlaces[i]); i++)
		{
			// printf("node %12s depth %d neighbor %s visited %d\n", node->name, depth, neighbor->name, neighbor->visited);
			if (!neighbor->visited)
			{
				neighbor->visited = 1;
				if (neighbor->hasCerealBar)
					enqueue(qSellers, neighbor);
				enqueue(queue, neighbor);
				prev++;
			}
		}
		c--;
		if (c == 0)
		{
			c = prev;
			prev = 0;
			depth++;
			if (!isEmpty(qSellers))
				break ;
		}
	}
	sellers = NULL;
	if (!isEmpty(qSellers))
	{
		n = sizeQueue(qSellers);
		sellers = malloc(sizeof(struct s_sellers));
		sellers->placeNames = malloc((n + 1) * sizeof(char *));
		sellers->distance = depth;
		idx = 0;
		while (!isEmpty(qSellers))
		{
			node = dequeue(qSellers);
			sellers->placeNames[idx++] = strdup(node->name);
		}
		sellers->placeNames[idx] = NULL;
	}
	return sellers;
}
