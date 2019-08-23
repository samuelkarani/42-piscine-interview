/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   knightOut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 22:12:56 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/21 12:28:03 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "header.h"

int rows[WIDTH] = {2, 2, 1, 1, -1, -1, -2, -2};
int cols[WIDTH] = {1, -1, 2, -2, 2, -2, 1, -1};

void printTable(double **table)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
			printf("%lf", table[i][j]);
		printf("\n");
	}
	printf("\n");
}

int valid(int i, int j)
{
    return i >= 0 && i < WIDTH && j >= 0 && j < WIDTH;
}

uint64_t getBoard(int i, int j)
{
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
	double sum, prob, r, c;
	int p, x, y;

	if (n == 0)
		return 1.0;
	p = getInitialPos(board);
	y = p / WIDTH, x = p % WIDTH;
	sum = 0;
	for (int i = 0; i < WIDTH; i++)
	{
		r = y + rows[i], c = x + cols[i];
		prob = valid(r, c) ? helper(getBoard(r, c), n - 1) : 0.0;
		sum += prob;
	}
	return sum / (double)WIDTH;
}

double knightOut2(uint64_t board, int n)
{
	if (getInitialPos(board) == -1 || n <= 0)
		return -1;
	return 1 - helper(board, n);
}

double **getTable()
{
	double **table = malloc(WIDTH * sizeof(double *));
	for (int i = 0; i < WIDTH; i++)
	{
		table[i] = malloc(WIDTH * sizeof(double));
		for (int j = 0; j < WIDTH; j++)
			table[i][j] = 0.0;
	}
	return table;
}

double knightOut(uint64_t board, int n)
{
	double res, **table, **nTable;
	int b, y, x;
	if (getInitialPos(board) == -1 || n <= 0)
		return -1;

	b = getInitialPos(board);
	table = getTable();
	y = b / WIDTH, x = b % WIDTH;
	table[y][x] = 1.0;
	for (int i = 0; i < n; i++)
	{
		nTable = getTable();
		for (int r = 0; r < WIDTH; r++)
		{
			for (int c = 0; c < WIDTH; c++)
			{
				if (fabs(table[r][c]) > 10e-7)
				{
					for (int l = 0; l < WIDTH; l++)
					{
						y = r + rows[l];
						x = c + cols[l];
						if (valid(y, x))
							nTable[y][x] += table[r][c] / (double)WIDTH;
					}
				}
			}
		}
		table = nTable;
		// printTable(table);
	}
	res = 0.0;
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < WIDTH; j++)
			res += table[i][j];
	return 1 - res;
}