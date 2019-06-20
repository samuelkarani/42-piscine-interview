/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:46:59 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/17 17:17:22 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "header.h"

char *rightShift(char *bin, int k)
{
    int i, sign;

    i = 5;
    sign = *bin == '1' ? '1' : '0';
    while (i - k >= 0)
    {
        bin[i] = bin[i - k];
        i--;
    }
    memset(bin, sign, k);
    return bin;
}

char *leftShift(char *bin, int k)
{
    int i;

    i = 0;
    while (i + k < 6)
    {
        bin[i] = bin[i + k];
        i++;
    }
    memset(bin + i, '0', k);
    return bin;
}

char *getSum(char *a, char *b)
{
    int carry, i;

    carry = 0;
    i = 5;
    while (i >= 0)
    {
        if (a[i] == '1' && b[i] == '1')
        {
            a[i] = '0' + carry;
            carry = 1;
        }
        else if (a[i] == '0' && b[i] == '0')
        {
            a[i] = carry + '0';
            carry = 0;
        }
        else
            a[i] = carry ? '0' : '1';
        i--;
    }
    return a;
}

char *getNot(char *s)
{
    int i;

    i = 5;
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

int toInt(char *bits)
{
    char *btscpy;
    int i, ret, neg;

    btscpy = strdup(bits);
    neg = 1;
    if (*btscpy == '1')
    {
        btscpy = getSum(btscpy, "111111");
        btscpy = getNot(btscpy);
        neg = -1;
    }
    i = ret = 0;
    while (btscpy[i])
    {
        ret *= 2;
        ret += btscpy[i] - '0';
        i++;
    }
    return ret * neg;
}