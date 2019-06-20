/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aloneCans.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 22:24:46 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/18 23:54:59 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "header.h"

void aloneCans(int *arr, int n)
{
	int x , a, i, b;

	i = x = a = b = 0;
	while (i < n)
	{
		x ^= arr[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		if (arr[i] & x)
			a = a ^ arr[i];
		else
			b = b ^ arr[i];
		i++;
	}
	printf("%d\n%d\n", a, b);
}