/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roulette.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:22:07 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/21 12:15:52 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#define BLK 18/37
#define RED 18/37
#define GRN  1/37

double probabilityWin(double firstDollarsBet, double dollarsWanted, int nbGame)
{
	if (firstDollarsBet < 0 || dollarsWanted < 0 || nbGame < 0)
		return 0.0;
    if (nbGame == 0 || firstDollarsBet == 0)
        return (double)(firstDollarsBet >= dollarsWanted);
    if (firstDollarsBet >= dollarsWanted)
        return 1.0;
	double sum = 0;
    sum += (double)RED * probabilityWin(firstDollarsBet * 2, dollarsWanted, nbGame - 1);
    sum += (double)GRN * probabilityWin(firstDollarsBet / 2, dollarsWanted, nbGame - 1);
    sum += (double)BLK * probabilityWin(0, dollarsWanted, nbGame - 1);
    return sum;
}
