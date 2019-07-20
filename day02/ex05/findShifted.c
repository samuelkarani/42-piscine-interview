/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findShifted.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 17:18:00 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/19 22:21:43 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int binarySearch(int *rocks, int n, int value)
{
    int start, end, mid;

    start = 0;
    end = n - 1;
    while (start <= end)
    {
        mid = (end + start) / 2;
        if (value == rocks[mid])
            return mid;
        else if (value > rocks[mid])
            start = mid + 1;
        else
            end = mid - 1;
    }
    return -1;
}

int	searchShifted(int *rocks, int length, int value)
{
    int pivot, i, found, a, b;

    found = 0;
    i = -1;
    while (++i < length - 1)
    {
        if (rocks[i] == value)
        {
            found = i;
            break ;
        }
        if (rocks[i] > rocks[i + 1])
        {
            pivot = i + 1;
            break ;
        }
    }
    if (found)
        return found;
    a = binarySearch(rocks, pivot, value);
    b = binarySearch(rocks + pivot, length - pivot, value);
    if (a == -1 && b == -1)
        return -1;
    return (a == -1 ? b : a);
}