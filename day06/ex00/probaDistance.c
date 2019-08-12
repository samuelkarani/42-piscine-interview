/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   probaDistance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 00:53:40 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/12 16:10:40 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"

double probaDistance(int dist, int *locations, int n)
{
	int count, total;

	count = total = 0;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (abs(locations[i] - locations[j]) > dist)
				count++;
			total++;
		}
	}
	return (double)count / total;
}
