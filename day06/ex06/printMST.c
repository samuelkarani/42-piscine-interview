/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printMST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:37:01 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/14 20:54:51 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "header.h"

int size(struct s_node **nodes)
{
	int i = 0;
	for (; nodes[i]; i++)
		;
	return i;
}

int find(int *nodes, int id)
{
	if (nodes[id] < 0)
		return id;
	return find(nodes, nodes[id]);
}

void funion(int *nodes, int x, int y)
{
	if (abs(nodes[x]) >= abs(nodes[y]))
	{
		nodes[x]--;
		nodes[y] = x;
	}
	else
	{
		nodes[y]--;
		nodes[x] = y;
	}
}

int cycle(int *nodes, int id1, int id2)
{
	int x = find(nodes, id1);
	int y = find(nodes, id2);
	if (x == y)
		return 1;
	return 0;
}

void printMST(struct s_graph *graph)
{
	struct s_node *node, *sNode;
	struct s_edge *edge, *sEdge;
	int n, smallest, idx;

	n = size(graph->nodes);
	int nodes[n];
	for (int i = 0; i < n; i++)
		nodes[i] = -1;
	idx = 0;
	for (int k = 1; k < n; k++)
	{
		smallest = INT_MAX;
		for (int i = 0; i < n; i++)
		{
			node = graph->nodes[i];
			for (int j = 0; node->edges[j]; j++)
			{
				edge = node->edges[j];
				if (edge->dist < smallest && !cycle(nodes, node->id, edge->dest->id))
				{
					sEdge = edge;
					smallest = edge->dist;
					sNode = node;
				}
			}
		}
		printf("%3d : %7s - %7s\n", sEdge->dist, sNode->name, sEdge->dest->name);
		funion(nodes, find(nodes, sNode->id), find(nodes, sEdge->dest->id));
	}
}