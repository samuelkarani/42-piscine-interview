/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maxTraffic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:57:58 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/16 15:56:39 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "header.h"

struct s_node *startNode(struct s_graph *graph, char *youAreHere)
{
    struct s_node *place, *start;
    start = NULL;

    for (int i = 0; (place = graph->places[i]); i++)
        if (!strcmp(place->name, youAreHere))
            start = place;
    return start;
}

void resetVisited(struct s_node **nodes)
{
	for (int i = 0; nodes[i]; i++)
		nodes[i]->visited = 0;
}

int getPaths(struct s_node *start, struct s_node *node)
{
	struct s_queue *queue;
	struct s_node *neighbor;
	int n, c, prev;

	queue = queueInit();
	node->visited = 1;
	enqueue(queue, node);
	n = 0, c = 1, prev = 0;
	while (queue->first)
	{
		node = dequeue(queue);
		if (node == start)
			n++;
		for (int j = 0; (neighbor = node->connectedPlaces[j]); j++)
		{
			if (!neighbor->visited)
			{
				if (neighbor != start)
					node->visited = 1;
				enqueue(queue, neighbor);
				prev++;
			}
		}
		c--;
		if (c == 0)
		{
			c = prev;
			prev = 0;
			if (n > 0)
				break ;
		}
	}
	return n;
}

float maxTraffic(struct s_graph *parisPlaces, char *eventHere)
{
	struct s_queue *queue;
	struct s_node *node, *start, *neighbor;
	int n;
	float mx;

	if (!(start = startNode(parisPlaces, eventHere)))
		return -1.0;
	for (int i = 0; (node = parisPlaces->places[i]); i++)
	{
		if (node == start)
			continue ;
		n = getPaths(start, node);
		printf("node %s paths %d\n", node->name, n);
		if (n)
			node->population /= n;
		resetVisited(parisPlaces->places);
	}
	queue = queueInit();
	start->visited = 1;
	start->population = 0;
	enqueue(queue, start);
	mx = 0.0;
	while (queue->first)
	{
		node = dequeue(queue);
		for (int i = 0; (neighbor = node->connectedPlaces[i]); i++)
		{
			if (!neighbor->visited)
			{
				neighbor->visited = 1;
				printf("neighbor %s population %d + %d\n", neighbor->name,neighbor->population, node->population);
				neighbor->population += node->population;
				enqueue(queue, neighbor);
				if (neighbor->population > mx)
					mx = neighbor->population;
			}
		}
	}
	return mx;
}