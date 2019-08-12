/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotspots.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:59:38 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/12 19:40:10 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "header.h"

int size(struct s_hotspot **hostspots)
{
    int i = 0;
    while (hostspots[i])
        i++;
    return i;
}

int overlap(struct s_hotspot *a, struct s_hotspot *b)
{
    return b->pos - b->radius < a->pos + a->radius;
}

int helper(struct s_hotspot **hotspots, int n, int *visited, int i)
{
	int count = 1;
	for (int j = i + 1; j < n; j++)
	{
		if (!visited[j] && !overlap(hotspots[i], hotspots[j]))
		{
			count++;
			visited[j] = 1;
			i = j;
		}
	}
	return count;
}

int selectHotspots(struct s_hotspot **hotspots)
{
	int n, count, *visited, mx;

	n = size(hotspots);
	visited = malloc(n * sizeof(int));
	memset(visited, 0, n * sizeof(int));
	mx = 0;
	for (int i = 0; i < n; i++)
	{
		if (!visited[i] && !overlap(hotspots[0], hotspots[i]))
		{
			count = 1 + helper(hotspots, n, visited, i);
			visited[i] = 1;
			if (count > mx)
				mx = count;
		}
	}
	return mx;
}