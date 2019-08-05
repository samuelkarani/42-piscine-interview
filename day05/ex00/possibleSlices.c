/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   possibleSlices.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 00:05:12 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/03 15:56:02 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"

void helper(int pizzaSlice, struct s_array *arr)
{
	if (arr->sum == pizzaSlice)
		return arrayPrint(arr);
	for (int i = pizzaSlice; i > 0; i--)
	{
		if (arr->sum + i <= pizzaSlice)
		{
			arrayAppend(arr, i);
			helper(pizzaSlice, arr);
			arrayDeque(arr);
		}
	}
}

void	printPossibleSlices(int pizzaSize)
{
	helper(pizzaSize, arrayInit());
}
