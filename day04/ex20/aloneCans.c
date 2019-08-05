/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aloneCans.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 22:24:46 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/03 01:33:53 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "header.h"

void aloneCans(int *arr, int n)
{
	int x = 0, a = 0, b = 0, i = 0;
	while (i < n)
	{
		x ^= arr[i];
		i++;
	}
	int rightmost = x & ~(x - 1);
	i = 0;
	while (i < n)
	{
		if (arr[i] & rightmost)
			a ^= arr[i];
		else
			b ^= arr[i];
		i++;
	}
	printf("%d\n%d\n", b, a);
}