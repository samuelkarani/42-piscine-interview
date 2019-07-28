/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 22:44:16 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/28 00:24:36 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void rotate(int **picture, int n)
{
	int tmp;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = i; j < n - i - 1; j++)
		{
			tmp = picture[i][j];
			picture[i][j] = picture[n - j - 1][i];
			picture[n - j - 1][i] = picture[n - i - 1][n - j - 1];
			picture[n - i - 1][n - j - 1] = picture[j][n - i - 1];
			picture[j][n - i - 1] = tmp;
		}
	}
}