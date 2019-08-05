/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bestPrice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 21:36:30 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/04 15:35:37 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"

double helper(int pizzaSlice, double *prices, double best, struct s_array *arr)
{
	if (arr->sum == pizzaSlice)
		return arrayPrice(arr, prices);
	for (int i = pizzaSlice; i > 0; i--)
	{
		if (arr->sum + i <= pizzaSlice)
		{
			arrayAppend(arr, i);
			double p = helper(pizzaSlice, prices, best, arr);
			if (p > best)
				best = p;
			arrayDeque(arr);
		}
	}
	return best;
}

double bestPrice2(int pizzaSize, double *prices)
{
	return helper(pizzaSize, prices, 0, arrayInit());
}

double bestPrice(int pizzaSize, double *prices)
{
	double d, best = prices[pizzaSize];
	for (int i = 1; i < pizzaSize / 2 + 1; i++)
		if ((d = bestPrice(i, prices) + bestPrice(pizzaSize - i, prices)) > best)
			best = d;
	return best;
}