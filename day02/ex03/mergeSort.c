/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergeSort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:04:18 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/14 16:20:49 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "header.h"

static int len(struct s_player **players)
{
    int count = 0;
    while (players[count])
        count++;
    return count;
}

static int bigger(struct s_player *a, struct s_player *b)
{
	return a->score > b->score;
}

void merge(struct s_player **a, int an, struct s_player **b, int bn, struct s_player **players)
{
	int i, j, idx;

	i = j = idx = 0;
	while (i < an && j < bn)
	{
		if (bigger(a[i], b[j]))
			players[idx++] = a[i++];
		else
			players[idx++] = b[j++];
	}
	while (i < an)
		players[idx++] = a[i++];
	while (j < bn)
		players[idx++] = b[j++];
}

void sort(struct s_player **players, int n)
{
    int mid, i;

    if (n < 2)
        return ;
    mid = n / 2;
    struct s_player *a[mid], *b[n - mid];
    i = -1;
   while (++i < mid)
		a[i] = players[i];
	i = mid - 1;
	while (++i < n)
		b[i - mid] = players[i];
    sort(a, mid);
    sort(b, n - mid);
    merge(a, mid, b, n - mid, players);
}

struct s_player **mergeSort(struct s_player **players)
{
    sort(players, len(players));
    return players;
}