/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   howManyJesus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 20:14:53 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/11 21:58:38 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "header.h"

static size_t prime = 3;

int expo(int n, int p)
{
    int res = 1;
    while (p-- > 0)
        res *= n;
    return res;
}

size_t hash(char *input, size_t n)
{
    size_t h, i;

    if (!input)
        return 0;
    h = *input;
    i = 1;
    while (i < n)
    {
        h += input[i] * expo(prime, i);
        i++;
    }
    return h;
}

int howManyJesus(char *bible, char *jesus)
{
    size_t h, count, len, n;

    if (!bible || !jesus)
        return -1;
    count = 0;
    len = strlen(jesus);
    h = hash(jesus, len);
    n = hash(bible, len);
    while (bible[len])
    {
        if (n != h)
            n = (n - *bible) / prime + expo(prime, len - 1) * bible[len];
        else if (strncmp(bible, jesus, len) == 0)
            count++;
        bible++;
    }
    if (h == n && strncmp(bible, jesus, len) == 0)
        count++;
    return count;
}