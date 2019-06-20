/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:48:40 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/17 15:22:14 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char *getNot(char *s)
{
    int i;

    i = 3;
    while (i >= 0)
    {
        if (s[i] == '0')
            s[i] = '1';
        else
            s[i] = '0';
        i--;
    }
    return s;
}

char *getAnd(char *a, char *b)
{
    int i;

    i = 3;
    if (*a == '~')
        a = getNot(a + 1);
    if (*b == '~')
        b = getNot(b + 1);
    while (i >= 0)
    {
        if (a[i] == '1' && b[i] == '1')
            a[i] = '1';
        else
            a[i] = '0';
        i--;
    }
    return a;
}

char *getOr(char *a, char *b)
{
    int i;

    i = 3;
    if (*a == '~')
        a = getNot(a + 1);
    if (*b == '~')
        b = getNot(b + 1);
    while (i >= 0)
    {
        if (a[i] == '0' && b[i] == '0')
            a[i] = '0';
        else
            a[i] = '1';
        i--;
    }
    return a;
}

int toInt(char *bits)
{
    int i;
    int ret;

    i = ret = 0;
    while (bits[i])
    {
        ret *= 2;
        ret += bits[i] - '0';
        i++;
    }
    return ret;
}