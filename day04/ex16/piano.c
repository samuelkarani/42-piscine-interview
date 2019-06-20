/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piano.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:53:55 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/18 18:05:09 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdlib.h>
#include "header.h"

int	**create(int width, int height)
{
    int **res = malloc(height * sizeof(int *));
    while (--height >= 0)
        res[height] = malloc(width * sizeof(int));
    return res;
}

int	**pianoDecompress(struct s_bit *bit, int l)
{
    int **res;
    int i, j;

    res = create(l, bit->n);
    i = -1;
    while (++i < bit->n)
    {
        j = -1;
        while (++j < l)
        {
            if ((bit->arr)[i] & (1 << j))
                res[i][j] = 1;
            else
                res[i][j] = 0;
        }
    }
    return res;
}