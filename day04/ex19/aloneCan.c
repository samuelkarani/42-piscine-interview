/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aloneCan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 21:04:43 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/18 22:11:16 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include "header.h"

void aloneCan(int *arr, int n)
{
    int i, res;

    i = -1; res = 0;
    while (++i < n)
        res ^= arr[i];
    printf("%d\n", res);
}