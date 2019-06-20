/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correctSong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:36:01 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/18 20:34:26 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "header.h"

void	correctSong(struct s_bit *bit, int l, int row, int col, int dist)
{
    (void)l;
    int i = -1;
    while (++i < dist)
        (bit->arr)[row + i] |= (int)pow(2, col);
}