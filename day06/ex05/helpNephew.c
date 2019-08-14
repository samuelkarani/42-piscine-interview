/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpNephew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 14:26:29 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/13 18:48:01 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double	probaNephewWillLive(int nStairs, int nPunch, int nephewStair)
{
	double sum, c, prob;
	if (nPunch == 0)
		return nStairs >= nephewStair;
	c = 1 / (double)nStairs;
	sum = 0.0;
	for (int i = nStairs; i > nephewStair + 1; i--)
	{
		prob =  c * probaNephewWillLive(i - 1, nPunch - 1, nephewStair);
		sum += prob;
	}
	return sum;
}