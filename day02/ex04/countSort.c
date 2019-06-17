/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countSort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:26:19 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/14 21:32:24 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "header.h"

void countSort(unsigned char *utensils, int n)
{
    unsigned char copy[n];
    int count_sum[15], i;

    memset(count_sum, 0, 15 * 4);
    i = -1;
    while (++i < n)
        count_sum[utensils[i] - 1] += 1;
    i = 0;
    while (++i < 15)
        count_sum[i] += count_sum[i - 1];
    i = -1;
    while (++i < n)
        copy[count_sum[utensils[i] - 1]-- - 1] = utensils[i];
    memcpy(utensils, copy, n);
}