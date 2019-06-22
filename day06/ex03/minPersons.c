/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minPersons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 19:59:23 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/20 21:59:31 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "header.h"

#define MAX 500

long double factorial(unsigned int n)
{
    static long double cache[MAX] = {0};
    if (n <= 1)
        return 1;
    if (cache[n])
        return cache[n];
    cache[n] = n * factorial(n - 1);
    return cache[n];
}

int		minPersons(int elements, int minPercentage)
{
    int i;
    long double d, p, f, e, c;

    e = (long double)elements;
    f = factorial(elements);
    p = 1 - (long double)minPercentage / 100;
    i = 1;
    while (i < elements)
    {
        c = factorial(elements - i);
        d = f / c / e;
        if (d <= p)
            break ;
        i++;
        e = e * elements;
    }
    return i;
}