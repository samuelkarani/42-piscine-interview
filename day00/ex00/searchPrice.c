/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchPrice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:24:52 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/11 23:16:55 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "header.h"

int	searchPrice(struct s_art **arts, char *name)
{
	if (!arts || !name)
		return -1;
	while (*arts)
	{
		if (strcmp((*arts)->name, name) == 0)
			return ((*arts)->price);
		arts++;
	}
	return (-1);
}
