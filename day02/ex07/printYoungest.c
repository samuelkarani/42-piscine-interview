/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printYoungest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 22:30:21 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/17 00:38:26 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "header.h"

int partition(int *ages, int start, int end)
{
    int pivotIdx, pivot, tmp;

    pivotIdx = (start + end) / 2;
    pivot = ages[pivotIdx];
    end++; start--;
    while (1)
    {
        do
            start++;
        while (ages[start] < pivot);
        do
            end--;
        while (ages[end] > pivot);
        if (start >= end)
            return end;
        tmp = ages[start];
        ages[start] = ages[end];
        ages[end] = tmp;
    }
}

void quicksort(int *ages, int start, int end)
{
    if (start < end)
    {
        int pivot = partition(ages, start, end);
        quicksort(ages, start, pivot);
        quicksort(ages, pivot + 1, end);
    }
}

void printYoungest(int *ages, int length)
{
    if (!ages || length <= 0)
        return ;
    quicksort(ages, 0, length - 1);
    printArray(ages, length);
    printf("youngest: %d\n", *ages);
}