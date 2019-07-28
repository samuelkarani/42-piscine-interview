/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   howManyJesus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 20:14:53 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/26 16:56:41 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "header.h"

static size_t prime = 3;

static int expo(int n, int p)
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
    i = 0;
    while (++i < n)
        h += input[i] * expo(prime, i);
    return h;
}

int howManyJesus(char *bible, char *jesus)
{
    size_t h, count, len, n;

    len = strlen(jesus);
    if (!bible || !jesus || strlen(bible) < len)
        return -1;
    count = 0;
    h = hash(jesus, len);
    n = hash(bible, len);
	bible += len;
    while (*bible)
    {
		if (n == h && !strncmp(&bible[-len], jesus, len))
            count++;
        n = (n - bible[-len]) / prime + expo(prime, len - 1) * *bible;
        bible++;
    }
	if (n == h && !strncmp(&bible[-len], jesus, len))
		count++;
    return count;
}