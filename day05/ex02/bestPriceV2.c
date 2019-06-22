/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bestPriceV2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 22:21:07 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/19 22:55:07 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double	helper(int size, double *prices, double *cache)
{
	double	price;
	if (size == 0 || cache[size] > 0)
		return (cache[size]);
	if (size == 1)
		return (cache[1]);
	cache[size] = prices[size];
	for (int i = 1; i < size; i++) {
		price = cache[i] + helper(size - i, prices, cache);
		if (price > cache[size])
			cache[size] = price;
	}
	return (cache[size]);
}

double	optimizedBestPrice(int pizzaSize, double *prices)
{
	double	cache[pizzaSize + 1];
	for (int i = 0; i <= pizzaSize; i++)
		cache[i] = 0;
	cache[1] = prices[1];
	return helper(pizzaSize, prices, cache);
}
