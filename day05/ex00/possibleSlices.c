/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   possibleSlices.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 00:05:12 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/19 21:27:20 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"

void	helper(int pizzaSize, struct s_array *a)
{
	for (int i = pizzaSize; i > 0; i--) {
		struct s_array *b = arrayClone(a);
		arrayAppend(b, i);
		if (b->sum == pizzaSize)
			arrayPrint(b);
		else if (b->sum < pizzaSize)
			helper(pizzaSize, b);
		free(b);
	}
}

void	printPossibleSlices(int pizzaSize)
{
	struct s_array *a;
	helper(pizzaSize, a = arrayInit());
	free(a);
}
