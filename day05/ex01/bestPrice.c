/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bestPrice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 21:36:30 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/19 22:16:38 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"

static double best;

void	helper(int pizzaSize, struct s_array *a, double *prices)
{
	for (int i = pizzaSize; i > 0; i--) {
		struct s_array *b = arrayClone(a);
		arrayAppend(b, i);
		if (b->sum == pizzaSize)
		{
            double price = arrayPrice(b, prices);
            if (price > best)
                best = price;
        }
		else if (b->sum < pizzaSize)
			helper(pizzaSize, b, prices);
		free(b);
	}
}

double bestPrice(int pizzaSize, double *prices)
{
    struct s_array *a;
    best = 0;
	helper(pizzaSize, a = arrayInit(), prices);
	free(a);
    return best;
}