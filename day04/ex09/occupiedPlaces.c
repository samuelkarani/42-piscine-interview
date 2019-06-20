/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occupiedPlaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 00:33:32 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/18 16:43:50 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int helper(unsigned int parkingRow, int count)
{
    if ((parkingRow & 1) == 1)
        count++;
    parkingRow >>= 1;
    if (parkingRow == 0)
        return count;
    return helper(parkingRow, count);
}

int occupiedPlaces2(unsigned int parkingRow)
{
    return helper(parkingRow, 0);
}

int dec(unsigned int n)
{
    return (n << 1) + ~n;
}

int inc(unsigned int n)
{
    int mask = 1;
    while (mask & n)
    {
        n &= ~mask;
        mask <<= 1;
    }
    return n | mask;
}

int occupiedPlaces(unsigned int parkingRow)
{
    int count = 0;
    while (parkingRow)
    {
        count = inc(count);
        parkingRow = dec(parkingRow) & parkingRow;
    }
    return count;
}
