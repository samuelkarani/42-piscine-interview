/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roulette.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:22:07 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/20 19:55:12 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#define BLACK 18/37
#define RED 18/37
#define GREEN 1/37

double calc(double p, double n)
{
    return p == (double)0 ? n : p * n;
}

double helper(double firstDollarsBet, double dollarsWanted, int nbGame, double p)
{
    if (firstDollarsBet == 0)
        return 0;
    if (nbGame == 0)
        return firstDollarsBet >= dollarsWanted ? p : 0;
    if (firstDollarsBet >= dollarsWanted)
        return p;
    double sum, e;
    sum = 0;
    sum += (e = helper(firstDollarsBet * 2, dollarsWanted, nbGame - 1, calc(p, (double)RED)));
    sum += (e = helper(firstDollarsBet / 2, dollarsWanted, nbGame - 1, calc(p, (double)GREEN)));
    sum += (e = helper(0, dollarsWanted, nbGame - 1, p * calc(p, (double)BLACK)));
    return sum;
}

double probabilityWin(double firstDollarsBet, double dollarsWanted, int nbGame)
{
    return helper(firstDollarsBet, dollarsWanted, nbGame, 0);
}