/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bestPriceV2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 22:21:07 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/04 16:43:23 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <string.h>

double bestPrice(int pizzaSize, double *prices, double *cache);

double check(int pizzaSize, double *prices, double *cache)
{
	if (pizzaSize == 0 || cache[pizzaSize])
		return cache[pizzaSize];
	return bestPrice(pizzaSize, prices, cache);
}

double bestPrice(int pizzaSize, double *prices, double *cache)
{
	cache[pizzaSize] = prices[pizzaSize];
	double d;
	for (int i = 1; i < pizzaSize / 2 + 1; i++)
		if ((d = check(i, prices, cache) + check(pizzaSize - i, prices, cache)) > cache[pizzaSize])
			cache[pizzaSize] = d;
	return cache[pizzaSize];
}

double	optimizedBestPrice(int pizzaSize, double *prices)
{
	double cache[pizzaSize + 1];
	memset(cache, 0, sizeof(double) * (pizzaSize + 1));
	cache[1] = prices[1];
	return bestPrice(pizzaSize, prices, cache);
}
