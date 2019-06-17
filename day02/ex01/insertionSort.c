/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertionSort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:21:51 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/14 13:40:33 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
void insertionSort(struct s_player **players)
{
    int i, hole;
    struct s_player *player;

    i = 1;
    while (players[i])
    {
        hole = i;
        player = players[i];
        while (hole > 0 && players[hole - 1]->score < player->score)
        {
            players[hole] = players[hole- 1];
            hole--;
        }
        players[hole] = player;
        i++;
    }
}