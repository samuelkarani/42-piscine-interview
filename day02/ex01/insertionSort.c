/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertionSort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:21:51 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/19 15:49:01 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
void insertionSort(struct s_player **players)
{
    struct s_player *player;
    int i, hole;

    i = 1;
    while (players[i])
    {
        hole = i;
        player = players[i];
        while (hole > 0 && players[hole - 1]->score < player->score)
        {
            players[hole] = players[hole - 1];
            hole--;
        }
        players[hole] = player;
        i++;
    }
}

void selectionSort(struct s_player **players)
{
    struct s_player *player;
    int largest;

    for (int i = 0; players[i]; i++)
    {
        largest = i;
        for (int j = i; players[j]; j++)
        {
            if (players[j]->score > players[largest]->score)
                largest = j;
        }
        player = players[i];
        players[i] = players[largest];
        players[largest] = player;
    }
}