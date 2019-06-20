/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updatePlace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 20:31:12 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/17 20:52:51 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "header.h"

unsigned int updatePlace(unsigned int parkingRow, int pos, int value)
{
    if (value)
        return parkingRow | (1 << pos);
    else
        return parkingRow & ~(1 << pos);
}