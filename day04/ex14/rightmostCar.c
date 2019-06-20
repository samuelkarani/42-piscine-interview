/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rightmostCar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:47:39 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/18 14:57:30 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int helper(unsigned int parkingRow, int count)
{
    if (parkingRow & 1)
        return count;
    return helper(parkingRow >> 1, count + 1);
}

int rightmostCar(unsigned int parkingRow)
{
    if (parkingRow == 0)
        return 0;
    return helper(parkingRow, 0);
}