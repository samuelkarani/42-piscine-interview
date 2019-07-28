/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchPriceV2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:47:01 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/26 15:34:13 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "header.h"

int searchPriceRecursive(struct s_art **arts, char *name, int start, int end)
{
	if (!name || !arts || start > end)
		return -1;
	int c, mid;
	mid = (start + end) / 2;
	c = strcmp(name, arts[mid]->name);
	if (!c)
		return arts[mid]->price;
	else if (c < 0)
		return searchPriceRecursive(arts, name, start, mid - 1);
	else
		return searchPriceRecursive(arts, name, mid + 1, end);
}

int searchPriceIterative(struct s_art **arts, int n, char *name)
{
	int start, end, mid, c;

	if (!name || !n || !arts)
		return -1;
	start = 0, end = n - 1;
	while (start <= end)
	{
		mid = (end + start) / 2;
		c = strcmp(name, arts[mid]->name);
		if (c == 0)
			return (arts[mid]->price);
		else if (c > 0)
			start = mid + 1;
		else
			end = mid - 1;
	}
	return -1;
}

int searchPrice(struct s_art **arts, int n, char *name)
{
	return 0 ? searchPriceIterative(arts, n, name) : searchPriceRecursive(arts, name, 0, n - 1);
}