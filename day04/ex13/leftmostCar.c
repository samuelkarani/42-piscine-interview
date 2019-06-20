/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leftmostCar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:31:03 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/18 14:39:31 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int helper(unsigned int parkingRow, int count)
{
    if (parkingRow == 0)
        return count;
    return helper(parkingRow >> 1, count + 1);
}

int leftmostCar(unsigned int parkingRow)
{
    return helper(parkingRow, -1);
}