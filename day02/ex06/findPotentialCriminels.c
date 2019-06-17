/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findPotentialCriminels.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 20:14:18 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/16 22:06:51 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "header.h"

int expo(int n, int p)
{
    int res = 1;
    while (p-- > 0)
        res *= n;
    return res;
}

int getDescription(struct s_info *info)
{
    return (
        info->gender * expo(10, 6)
        + info->height * expo(10, 5)
        + info->hairColor * expo(10, 4)
        + info->eyeColor * expo(10, 3)
        + info->glasses * expo(10, 2)
        + info->tattoo * 10
        + info->piercing
    );
}

int val(int n, int i)
{
    while (i-- > 0 && n)
        n /= 10;
    return n % 10;
}

int count(struct s_criminal **criminals)
{
    int count = 0;
    while (criminals[count])
        count++;
    return count;
}

void countSort(struct s_criminal **criminals, int n, int idx)
{
    struct s_criminal *copy[n];
    int count_sum[10], i;

    memset(count_sum, 0, 10 * sizeof(int));
    i = -1;
    while (criminals[++i])
        count_sum[val(criminals[i]->description, idx)] += 1;
    i = 0;
    while (++i < 10)
        count_sum[i] += count_sum[i - 1];
    i = 10;
    while (--i > 0)
        count_sum[i] = count_sum[i - 1];
    count_sum[0] = 0;
    i = -1;
    while (criminals[++i])
        copy[count_sum[val(criminals[i]->description, idx)]++] = criminals[i];
    memcpy(criminals, copy, n * sizeof(struct s_criminal *));
}

static int len;

void sortCriminals(struct s_criminal **criminals)
{
    int i, n;

    len = count(criminals);
    n = 7;
    i = -1;
    while (++i < n)
        countSort(criminals, len, i);
}

struct s_criminal **findPotentialCriminals(struct s_criminal **criminals, struct s_info *info)
{
    int start, end, mid, info_val, idx;
    struct s_criminal **res;
    struct s_criminal *buf[len];

    info_val = getDescription(info);
    idx = 0;
    start = 0;
    end = len -1;
    while (start <= end)
    {
        mid = (start + end) / 2;
        if (info_val == criminals[mid]->description)
        {
            while (info_val == criminals[mid]->description)
                mid--;
            while (info_val == criminals[++mid]->description)
                buf[idx++] = criminals[mid];
            break ;
        }
        else if (info_val > criminals[mid]->description)
            start = mid + 1;
        else
            end = mid - 1;
    }
    res = malloc((idx + 1) * sizeof(struct s_criminal *));
    res[idx] = NULL;
    memcpy(res, buf, idx * sizeof(struct s_criminal *));
    return res;
}