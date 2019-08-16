/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotspots.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:59:38 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/16 15:48:10 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "header.h"

int overlap(struct s_hotspot *a, struct s_hotspot *b)
{
    return b->pos - b->radius < a->pos + a->radius;
}

int size(struct s_hotspot **hotspots)
{
	int i = 0;
	for (; hotspots[i]; i++)
		;
	return i;
}

int helper(struct s_hotspot **hotspots, int n, int idx, int *visited)
{
	int mx, count;

	mx = 0, count = 0;
	for (int i = idx + 1; hotspots[i]; i++)
	{
		if (!visited[i] && !overlap(hotspots[idx], hotspots[i]))
		{
			visited[i] = 1;
			count = 1 + helper(hotspots, n, i, visited);
			if (count > mx)
				mx = count;
		}
	}
	return mx;
}

int selectHotspots(struct s_hotspot **hotspots)
{
	int n = size(hotspots);
	int visited[n];
	memset(visited, 0, n * sizeof(int));
	return helper(hotspots, n, 0, visited) + 1;
}