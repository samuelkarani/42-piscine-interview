/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decrypt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:08:10 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/17 17:17:56 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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