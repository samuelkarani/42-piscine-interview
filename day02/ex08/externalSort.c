/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externalSort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 00:57:18 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/30 00:36:49 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "header.h"

static char fname[20];
#define S_NAME "sorted%d.tmp"

static void openFiles(FILE **fps, int n)
{
	int i = -1;
	while (++i < n)
	{
		sprintf(fname, S_NAME, i);
		fps[i] = openFile(fname, "r");
	}
}

static void closeFiles(FILE **fps, int n)
{
	int i = -1;
	while (++i < n)
		fclose(fps[i]);
}

int partition(int *arr, int start, int end)
{
    int pivotIdx, pivot, tmp;

    pivotIdx = (start + end) / 2;
    pivot = arr[pivotIdx];
    end++; start--;
    while (1)
    {
        do
            start++;
        while (arr[start] < pivot);
        do
            end--;
        while (arr[end] > pivot);
        if (start >= end)
            return end;
        tmp = arr[start];
        arr[start] = arr[end];
        arr[end] = tmp;
    }
}

void quicksort(int *arr, int start, int end)
{
    if (start < end)
    {
        int pivot = partition(arr, start, end);
        quicksort(arr, start, pivot);
        quicksort(arr, pivot + 1, end);
    }
}

void externalSort(char *scoreFile, char *sortedFile, int ram)
{
	FILE *fp, *res;
	int n, *arr, i, j;

	// part 1
	fp = openFile(scoreFile, "r");
	arr = malloc(sizeof(int) * ram);
	i = 0;
	while ((n = readBlock(fp, arr, ram)))
	{
		quicksort(arr, 0, n);
		sprintf(fname, S_NAME, i);
		writeFile(fname, arr, n);
		i++;
	}
	fclose(fp);

	FILE *files[i];
	t_block blocks[i];
	int smallest, oidx, l, ostart, isize, prev, stop;

	// part 2
	res = openFile(sortedFile, "w");
	memset(blocks, 0, sizeof(t_block) * i);
	ostart = ram - ram * 0.2;
	isize = ostart / i;
	openFiles(files, i);
	stop = 0;
	while (!stop)
	{
		oidx = ostart;
		while (oidx < ram)
		{
			smallest = INT_MAX;
			prev = -1;
			j = 0;
			while (j < i)
			{
				if (!blocks[j].n)
				{
					l = isize * j;
					blocks[j].n = readBlock(files[j], arr + l, isize);
					blocks[j].i = l;
				}
				if (blocks[j].n && arr[blocks[j].i] < smallest)
				{
					smallest = arr[blocks[j].i++];
					blocks[j].n--;
					if (prev != -1)
					{
						blocks[prev].i--;
						blocks[prev].n++;
					}
					prev = j;
				}
				j++;
			}
			if (smallest == INT_MAX)
			{
				stop = 1;
				break ;
			}
			arr[oidx++] = smallest;
		}
		writeFileFP(res, &arr[ostart], oidx - ostart);
	}
	closeFiles(files, i);
	fclose(res);
}