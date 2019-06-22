/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heapSort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:41:35 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/21 15:30:40 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "header.h"

void swap(struct s_art **arts, int i, int j)
{
    struct s_art *tmp = arts[i];
    arts[i] = arts[j];
    arts[j] = tmp;
}

int cmp(struct s_art *a, struct s_art *b)
{
    return strcmp(a->name, b->name) > 0;
}

void heapify(struct s_art **masterpiece, int n, int idx)
{
    int left, right, largest;

    largest = idx;
    left = idx * 2 + 1;
    right = idx * 2 + 2;
    if (left < n && cmp(masterpiece[largest], masterpiece[left]) == 0)
        largest = left;
    if (right < n && cmp(masterpiece[largest], masterpiece[right]) == 0)
        largest = right;
    if (largest != idx)
    {
        swap(masterpiece, largest, idx);
        heapify(masterpiece, n, largest);
    }
}

void heapSort(struct s_art **masterpiece, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(masterpiece, n, i);
    for (int i = n - 1; i >= 0; i--)
    {
        swap(masterpiece, 0, i);
        heapify(masterpiece, i, 0);
    }
}