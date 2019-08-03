/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carPosition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 12:20:15 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/02 17:54:43 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int helper(unsigned int parkingRow, int pos)
{
    if ((parkingRow & 1))
        return pos;
    if (parkingRow == 0)
        return -1;
    return helper(parkingRow >> 1, pos + 1);
}

int carPosition(unsigned int parkingRow)
{
    return helper(parkingRow, 0);
}