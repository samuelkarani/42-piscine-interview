/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sinkIsland.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:08:15 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/03 19:09:24 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void sinkIsland(int **map, int row, int col)
{
    int c = map[row][col];
    map[row][col] = 0;
    if (row > 0 && map[row - 1][col] == c)
        sinkIsland(map, row - 1, col);
    if (map[row + 1] && map[row + 1][col] == c)
        sinkIsland(map, row + 1, col);
    if (col > 0 && map[row][col - 1] == c)
        sinkIsland(map, row, col - 1);
    if (map[row][col + 1] != -1 && map[row][col + 1] == c)
        sinkIsland(map, row, col + 1);
}