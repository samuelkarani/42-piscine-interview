/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roulette.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:22:07 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/12 21:18:54 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#define BLK 18/37
#define RED 18/37
#define GRN  1/37

double calc(double p, double k)
{
    return p == (double)0 ? k : p * k;
}

double helper(double firstDollarsBet, double dollarsWanted, int nbGame, double p)
{
    if (nbGame == 0 || firstDollarsBet == 0)
        return firstDollarsBet >= dollarsWanted ? calc(p, 1) : 0;
    if (firstDollarsBet >= dollarsWanted)
        return calc(p, 1);
    double sum;
    sum = 0;
    sum += helper(firstDollarsBet * 2, dollarsWanted, nbGame - 1, calc(p, (double)RED));
    sum += helper(firstDollarsBet / 2, dollarsWanted, nbGame - 1, calc(p, (double)GRN));
    sum += helper(0, dollarsWanted, nbGame - 1, calc(p, (double)BLK));
    return sum;
}

double probabilityWin(double firstDollarsBet, double dollarsWanted, int nbGame)
{
	if (firstDollarsBet < 0 || dollarsWanted < 0 || nbGame < 0)
		return 0;
    return helper(firstDollarsBet, dollarsWanted, nbGame, 0);
}
