/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isFilled.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 20:57:04 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/18 00:31:35 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int isFilled(unsigned int parkingRow)
{
    if ((parkingRow & 1) == 0)
        return 0;
    parkingRow >>= 1;
    if (parkingRow == 0)
        return 1;
    else
        return isFilled(parkingRow);
}