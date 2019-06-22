/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   knightOut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 22:12:56 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/21 00:16:40 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "header.h"

void pos(int n, int *res)
{
    res[0] = n / 8;
    res[1] = n % 8;
}

int val(int i, int j)
{
    return i * 8 + j;
}

int valid(int i, int j)
{
    return i >= 0 && i < 8 && j >= 0 && j < 8;
}

uint64_t clear(uint64_t board, int pos)
{
    return board & ~(1 << pos);
}

uint64_t set(uint64_t board, int pos)
{
    return board | (1 << pos);
}

int getInitialPos(uint64_t board)
{
    int i, count, pos;

    i = count = pos = 0;
    while (i < 64)
    {
        if (board & (1 << i))
        {
            pos = i;
            count++;
            break ;
        }
        i++;
    }
    return count == 1 ? pos : -1;
}

uint64_t prepare(uint64_t board, int n, int i, int j)
{
    int v;

    board = clear(board, n);
    v = val(i, j);
    board = set(board, v);
    return board;
}

unsigned long helper(uint64_t board, int n, int count)
{
    int idx, i, j, p[2], a, b, c, d, e, f, g, h;
    idx = getInitialPos(board);
    pos(idx, p);
    i = p[0], j = p[1];
    if (n == 0 || !valid(i, j))
        return count;
    count += a = !valid(i - 1, j - 2);
    count = helper(prepare(board, n, i - 1, j - 2), n - 1, count);
    count += b = !valid(i - 1, j + 2);
    count = helper(prepare(board, n, i - 1, j + 2), n - 1, count);
    count += c = !valid(i + 1, j - 2);
    count = helper(prepare(board, n, i + 1, j - 2), n - 1, count);
    count += d = !valid(i + 1, j + 2);
    count = helper(prepare(board, n, i + 1, j + 2), n - 1, count);
    count += e = !valid(i - 2, j - 1);
    count = helper(prepare(board, n, i - 2, j - 1), n - 1, count);
    count += f = !valid(i - 2, j + 1);
    count = helper(prepare(board, n, i - 2, j + 1), n - 1, count);
    count += g = !valid(i + 2, j - 1);
    count = helper(prepare(board, n, i + 2, j - 1), n - 1, count);
    count += h = !valid(i + 2, j + 1);
    count = helper(prepare(board, n, i + 2, j + 1), n - 1, count);
    return count;
}

double knightOut(uint64_t board, int n)
{
    int pos;

    if ((pos = getInitialPos(board)) == -1 || n < 0)
        return -1;
    return (double)helper(board, n, 0) / pow(8, n);
}
