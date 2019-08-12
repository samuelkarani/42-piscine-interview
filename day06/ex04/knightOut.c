/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   knightOut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 22:12:56 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/12 23:30:05 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "header.h"

typedef struct s_point
{
	int i;
	int j;
} t_point;

t_point pos(int n)
{
	return (t_point){n / WIDTH, n % WIDTH};
}

int valid(int i, int j)
{
    return i >= 0 && i < WIDTH && j >= 0 && j < WIDTH;
}

uint64_t getVal(int i, int j)
{
	if (!valid(i, j))
		return 0;
	return 1ULL << (i * WIDTH + j);
}

int getInitialPos(uint64_t board)
{
	int res = 0, c = 0;
	for (int i = 0; i < WIDTH * WIDTH; i++)
		if (board & 1ULL << i)
		{
			res = i;
			c++;
		}
	return c == 1 ? res : -1;
}

double helper(uint64_t board, int n)
{
	double res;
	int p;
	t_point point;
	uint64_t newBoard;
	if (n == 0)
		return (double)1;
	p = getInitialPos(board);
	point = pos(p);
	res = 0;
	newBoard = getVal(point.i - 1, point.j - 2);
	res += newBoard ? 1 / (double)WIDTH * helper(newBoard, n - 1) : 0;
	newBoard = getVal(point.i - 1, point.j + 2);
	res += newBoard ? 1 / (double)WIDTH * helper(newBoard, n - 1) : 0;
	newBoard = getVal(point.i + 1, point.j - 2);
	res += newBoard ? 1 / (double)WIDTH * helper(newBoard, n - 1) : 0;
	newBoard = getVal(point.i + 1, point.j + 2);
	res += newBoard ? 1 / (double)WIDTH * helper(newBoard, n - 1) : 0;
	newBoard = getVal(point.i - 2, point.j - 1);
	res += newBoard ? 1 / (double)WIDTH * helper(newBoard, n - 1) : 0;
	newBoard = getVal(point.i - 2, point.j + 1);
	res += newBoard ? 1 / (double)WIDTH * helper(newBoard, n - 1) : 0;
	newBoard = getVal(point.i + 2, point.j - 1);
	res += newBoard ? 1 / (double)WIDTH * helper(newBoard, n - 1) : 0;
	newBoard = getVal(point.i + 2, point.j + 1);
	res += newBoard ? 1 / (double)WIDTH * helper(newBoard, n - 1) : 0;
	return 1 - res;
}

double knightOut(uint64_t board, int n)
{
	if (getInitialPos(board) == -1 || n <= 0)
		return -1;
	return helper(board, n);
}