/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quickSort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:47:01 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/14 15:53:46 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int len(struct s_player **players)
{
    int count = 0;
    while (players[count])
        count++;
    return count;
}

void swap(struct s_player *a, struct s_player *b)
{
    char *tmpn;
    int tmps;

    tmpn = a->name;
    tmps = a->score;
    a->name = b->name;
    a->score = b->score;
    b->name = tmpn;
    b->score = tmps;
}

int partition(struct s_player **players, int start, int end)
{
    int pIndex, i;

    pIndex = start;
    for (i = start; i < end; i++)
    {
        if (players[i]->score <= players[end]->score)
            swap(players[i], players[pIndex++]);
    }
    swap(players[pIndex], players[end]);
    return pIndex;
}

void sort(struct s_player **players, int start, int end)
{
    if (start < end)
    {
        int pIndex = partition(players, start, end);
        sort(players, start, pIndex - 1);
        sort(players, pIndex + 1, end);
    }
}

void quickSort(struct s_player **players)
{
    sort(players, 0, len(players) - 1);
}

