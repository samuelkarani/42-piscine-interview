/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotspots.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:59:38 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/20 15:53:46 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "header.h"

int size(struct s_hotspot **hostspots)
{
    int i = 0;
    while (hostspots[i])
        i++;
    return i;
}

int overlapping(struct s_hotspot *a, struct s_hotspot *b)
{
    return b->pos - b->radius < a->pos + a->radius;
}

int selectHotspots(struct s_hotspot **hotspots)
{
    int i, j, mx, count, idx, n;
    
    n = size(hotspots);
    int cache[n];
    memset(cache, 0, sizeof(int) * n);
    i = mx = 0;
    while (hotspots[i])
    {
        count = j = 0;
        idx = i;
        while (hotspots[j])
        {
            if (idx != j && j != i && !cache[j])
            {
                if (!overlapping(hotspots[idx], hotspots[j])
                    && !overlapping(hotspots[i], hotspots[j]))
                {
                    idx = j;
                    count++;
                    cache[j] = 1;
                }
            }
            j++;
        }
        if (count > mx)
            mx = count;
        i++;
    }
    return mx + 1;
}