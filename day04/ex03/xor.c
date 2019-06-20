/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:26:37 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/17 19:30:47 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char *getXor(char *a, char *b)
{
    int i = 0;

    while (a[i] && b[i])
    {
        if ((a[i] == '0' && b[i] == '0')
            || (a[i] == '1' && b[i] == '1'))
            a[i] = '0';
        else
            a[i] = '1';
        i++;
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