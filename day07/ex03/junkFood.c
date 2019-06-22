/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junkFood.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:01:11 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/22 00:00:39 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "header.h"

int sizeStart(struct s_graph *graph, char *youAreHere, struct s_node **start)
{
    struct s_node *place;
    int i = 0;

    *start = NULL;
    while ((place = graph->places[i]))
    {
        if (strcmp(place->name, youAreHere) == 0)
            *start = place;
        i++;
    }
    return i;
}

static int depth;

int helper(struct s_queue *queue, struct s_sellers *res, int idx)
{
    
    struct s_node *start, *neighbor;
    int i;

    start = dequeue(queue);
    if (!start)
        return idx;
    start->visited = 1;
    if (start->hasCerealBar)
        res->placeNames[idx++] = start->name;
    else
    {
        i = -1;
        while ((neighbor = start->connectedPlaces[++i]))
        {
            if (!neighbor->visited)
                enqueue(queue, neighbor);
        }
        idx = helper(queue, res, idx);
        depth++;
    }
    res->distance = depth;
    return idx;
}

#include <stdio.h>
struct s_sellers *closestSellers(struct s_graph *graph, char *youAreHere)
{
    struct s_sellers *res;
    int count, n;
    struct s_node *start;
    struct s_queue *queue;

    res = malloc(sizeof(struct s_sellers));
    count = sizeStart(graph, youAreHere, &start);
    char *placeNames[count];
    res->placeNames = placeNames;
    depth = 0;
    queue = queueInit();
    enqueue(queue, start);
    n = helper(queue, res, 0);
    res->placeNames = malloc(n * sizeof(char *));
    int i = -1;
    while (++i < n)
        printf("%d %s\n", i, placeNames[i]);
    memcpy(res->placeNames, placeNames, sizeof(char *) * n);
    return res;
}
