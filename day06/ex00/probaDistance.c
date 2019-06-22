/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   probaDistance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 00:53:40 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/20 16:56:13 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "header.h"

static int totalCount;

int sum(int *locations, int i, int j)
{
    return locations[i] + locations[j];
}

int helper(int dist, int *locations, int n, int idx, int count, int *cache)
{
    int i = idx + 1;
    while (i < n)
    {
        if (i != idx)
        {
            if (abs(locations[idx] - locations[i]) > dist)
                count += 1;
            if (i + 1 < n && !cache[sum(locations, i, i + 1)])
                count = helper(dist, locations, n, i, count, cache);
            totalCount += 1;
            cache[sum(locations, idx, i)] = 1;
        }
        i++;
    }
    return count;
}

double probaDistance(int dist, int *locations, int n)
{
    totalCount = 0;
    int clen = (locations[n - 1]) + (n > 1 ? locations[n - 2] : 0);
    int cache[clen];
    memset(cache, 0, sizeof(int) * clen);
    int count = helper(dist, locations, n, 0, 0, cache);
    return (double)count / (double)totalCount;
}