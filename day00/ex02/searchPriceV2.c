/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchPriceV2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:47:01 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/11 23:18:24 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "header.h"

int	len(struct s_art **arts)
{
	int count = 0;
	while (*arts++)
		count++;
	return count;
}

int searchPrice(struct s_art **arts, int n, char *name)
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