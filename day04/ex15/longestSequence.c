/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longestSequence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:56:58 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/18 17:31:11 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int longestSequence(unsigned int parkingRow)
{
    int count = 0;
    while (parkingRow)
    {
        parkingRow = (parkingRow << 1) & parkingRow;
        count = inc(count);
    }
    return count;
}