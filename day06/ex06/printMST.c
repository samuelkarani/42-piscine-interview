/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printMST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:37:01 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/14 16:17:21 by smbaabu          ###   ########.fr       */
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

struct s_connection
{
	struct s_node *a;
	struct s_node *b;
};

void fsort(struct s_edge **edges)
{
	struct s_edge *tmp;

	for (int i = 0; edges[i + 1]; i++)
	{
		for (int j = 0; edges[j + 1]; j++)
		{
			if (edges[j]->dist > edges[j + 1]->dist)
			{
				tmp = edges[j];
				edges[j] = edges[j + 1];
				edges[j + 1] = tmp;
			}
		}
	}
}

int contains(struct s_connection *connections, int n, struct s_node *a, struct s_node *b)
{
	for (int i = 0; i < n; i++)
		if ((connections[i].a == a && connections[i].b == b)
			|| (connections[i].a == b && connections[i].b == a))
			return 1;
	return 0;
}

void print(struct s_node *sNode, struct s_edge *sEdge)
{
	printf("%3d : %7s - %7s\n", sEdge->dist, sNode->name, sEdge->dest->name);
}

void printMST(struct s_graph *graph)
{
	struct s_node *node, *sNode, *front, *back;
	struct s_edge *edge, *sEdge, *fEdge, *bEdge;
	int n, fsmall, bsmall, small, idx, cost;

	n = size(graph->nodes);
	struct s_connection connections[n];
	idx = 0;
	for (int i = 1; i < n; i++)
	{
		if (i == 1)
		{
			small = INT_MAX;
			for (int i = 0; i < n; i++)
			{
				node = graph->nodes[i];
				fsort(node->edges);
				for (int j = 0; node->edges[j]; j++)
				{
					edge = node->edges[j];
					// printf("pre: %d -> %s - %s\n", edge->dist, node->name, edge->dest->name);
					if (edge->dist < small && !contains(connections, idx, node, edge->dest))
					{
						sEdge = edge;
						small = edge->dist;
						sNode = node;
						break ;
					}
				}
			}
			connections[idx++] = (struct s_connection){sNode, sEdge->dest};
			front = sNode;
			back = sEdge->dest;
			print(sNode, sEdge);
		}
		else
		{
			fsmall = INT_MAX;
			for (int i = 0; front->edges[i]; i++)
			{
				edge = front->edges[i];
				// printf("front: %d -> %s - %s\n", edge->dist, front->name, edge->dest->name);
				if (edge->dist < fsmall && !contains(connections, idx, front, edge->dest))
					{
						fEdge = edge;
						fsmall = edge->dist;
						break ;
					}
			}
			bsmall = INT_MAX;
			for (int i = 0; back->edges[i]; i++)
			{
				edge = back->edges[i];
				// printf("back: %d -> %s - %s\n", edge->dist, back->name, edge->dest->name);
				if (edge->dist < bsmall && !contains(connections, idx, back, edge->dest))
					{
						bEdge = edge;
						bsmall = edge->dist;
						break ;
					}
			}
			if (fsmall < bsmall)
			{
				connections[idx++] = (struct s_connection){front, fEdge->dest};
				print(front, fEdge);
				front = fEdge->dest;
			}
			else
			{
				connections[idx++] = (struct s_connection){back, bEdge->dest};
				print(back, bEdge);
				back = bEdge->dest;
			}
		}
	}
	printf("cost: %d", cost);
}

int cycle(struct s_edge **edges, struct s_edge *edge);

void printMST2(struct s_graph *graph)
{
	struct s_node *node, *sNode;
	struct s_edge *edge, *sEdge;
	int n, count, smallest, i, j;

	n = size(graph->nodes);
	struct s_edge *sEdges[n];
	struct s_node *sNodes[n];
	count = 0, i = 0, j = 0;
	for (int k = 1; k < n; k++)
	{
		smallest = INT_MAX;
		for (int i = 0; i < n; i++)
		{
			node = graph->nodes[i];
			for (int j = 0; node->edges[j]; j++)
			{
				edge = node->edges[j];
				if (edge->dist < smallest)
				{
					sEdge = edge;
					smallest = edge->dist;
					sNode = node;
				}
			}
		}
		printf("%3d : %7s - %7s\n", sEdge->dist, sNode->name, sEdge->dest->name);
		sNodes[i++] = sNode;
		sEdges[j++] = sEdge;
		sEdge->dist = INT_MAX;
	}
}