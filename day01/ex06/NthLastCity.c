/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NthLastCity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 17:00:05 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/13 18:47:51 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char *NthLastCity(struct s_city *city, int n)
{
	struct s_city *p, *f;
	int i;

	if (n < 0)
		return 0;
	p = f = city;
	i = -1;
	while (++i < n && f)
		f = f->next;
	if (i < n)
		return 0;
	while (f->next)
	{
		p = p->next;
		f = f->next;
	}
	return p->name;
}