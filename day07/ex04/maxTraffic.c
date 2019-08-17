/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maxTraffic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:57:58 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/16 19:25:08 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "header.h"

struct s_node *startNode(struct s_graph *graph, char *youAreHere)
{
    struct s_node *place;
    for (int i = 0; (place = graph->places[i]); i++)
        if (!strcmp(place->name, youAreHere))
            return place;
    return NULL;
}

int setDepths(struct s_node *node)
{
	struct s_queue *queue;
	struct s_node *neighbor;
	int d;

	queue = queueInit();
	node->visited = 1;
	enqueue(queue, node);
	d = 0;
	while (queue->first)
	{
		node = dequeue(queue);
		for (int j = 0; (neighbor = node->connectedPlaces[j]); j++)
		{
			if (!neighbor->visited)
			{
				d = neighbor->visited = node->visited + 1;
				enqueue(queue, neighbor);
			}
		}
	}
	return d;
}

int size(struct s_node **nodes)
{
	int i = 0;
	for (; nodes[i]; i++)
		;
	return i;
}

int getNodes(struct s_node **nodes, int depth, struct s_node **res)
{
	int idx = 0;
	for (int i = 0; nodes[i]; i++)
	{
		if (nodes[i]->visited == depth)
			res[idx++] = nodes[i];
	}
	return idx;
}

int contains(struct s_node **nodes, struct s_node *node)
{
	for (int i = 0; nodes[i]; i++)
		if (nodes[i] == node)
			return 1;
	return 0;
}

int getParents(struct s_node **nodes, struct s_node *node, struct s_node **res)
{
	int idx = 0;
	for (int i = 0; nodes[i]; i++)
	{
		if (nodes[i]->visited == node->visited - 1 && contains(nodes[i]->connectedPlaces, node))
			res[idx++] = nodes[i];
	}
	return idx;
}

float maxTraffic(struct s_graph *parisPlaces, char *eventHere)
{
	struct s_node *node, *start, *parent;
	int n, d, c, p, s, mx;

	if (!(start = startNode(parisPlaces, eventHere)))
		return -1.0;
	d = setDepths(start);
	n = size(parisPlaces->places);
	struct s_node *nodes[n], *parents[n];
	start->population = 0;
	for (int i = d; i > 1; i--)
	{
		c = getNodes(parisPlaces->places, i, nodes);
		for (int j = 0; j < c; j++)
		{
			node = nodes[j];
			if (node == start)
				continue ;
			p = getParents(parisPlaces->places, node, parents);
			if (p > 0 && (s = node->population / p) > 0)
			{
				for (int k = 0; k < p; k++)
				{
					parent = parents[k];
					parent->population += s;
				}
			}
		}
	}
	mx = 0;
	for (int i = 0; (node = start->connectedPlaces[i]); i++)
		if (node->population > mx)
			mx = node->population;
	return (float)mx;
}