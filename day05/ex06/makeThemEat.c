/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makeThemEat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 16:59:49 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/04 20:15:56 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int helper(struct s_people **people, int *tables, int nbTable, int idx)
{
	if (!people[idx])
		return 1;
	for (int i = 0; i < nbTable; i++)
		if (tables[i] - people[idx]->time >= 0)
		{
			tables[i] -= people[idx]->time;
			if (helper(people, tables, nbTable, idx + 1))
				return 1;
			tables[i] += people[idx]->time;
		}
	return 0;
}

int isPossible(struct s_people **people, int nbTable, int totalTime)
{
	int tables[nbTable];
	for (int i = 0; i < nbTable; i++)
		tables[i] = totalTime;
	return people ? helper(people, tables, nbTable, 0) : 0;
}