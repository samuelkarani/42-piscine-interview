/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carPosition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 12:48:32 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/18 13:39:46 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "header.h"

int carPosition(unsigned int parkingRow)
{
    if (parkingRow == 0 || parkingRow % 2 == 1)
        return 0;
    else
    {
        double x = log2(parkingRow);
        if (ceil(x) == floor(x))
            return (int)x;
        else
        {
            int i = 1;
            while (parkingRow % (unsigned int)pow(2, i) == 0)
                i++;
            return i - 1;
        }
    }
}