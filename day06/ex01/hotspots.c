/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotspots.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:59:38 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/14 19:43:20 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int overlap(struct s_hotspot *a, struct s_hotspot *b)
{
    return b->pos - b->radius < a->pos + a->radius;
}

int selectHotspots(struct s_hotspot **hotspots)
{
	int idx, n;

	idx = 0, n = 1;
	for (int i = 1; hotspots[i]; i++)
	{
		if (!overlap(hotspots[idx], hotspots[i]))
		{
			n++;
			idx = i;
		}
	}
	return n;
}