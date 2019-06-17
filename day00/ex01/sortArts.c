/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortArts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:52:31 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/11 23:17:33 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "header.h"

static int ascending(char *a, char *b)
{
	return strcmp(a, b) <= 0;
}

void bubble(struct s_art **arts)
{
	int i, j;
	struct s_art *tmp;

	i = 0;
	while (arts[i + 1])
	{
		j = 0;
		while (arts[j + 1])
		{
			if (ascending(arts[j]->name, arts[j + 1]->name) == 0)
			{
				tmp = arts[j];
				arts[j] = arts[j + 1];
				arts[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int ascending_s(struct s_art *a, struct s_art *b)
{
	return strcmp(a->name, b->name) <= 0;
}

void merge(struct s_art **a, int an, struct s_art **b, int bn, struct s_art **arts)
{
	int i, j, idx;
	i = j = idx = 0;
	while (i < an && j < bn)
	{
		if (ascending_s(a[i], b[j]))
			arts[idx++] = a[i++];
		else
			arts[idx++] = b[j++];
	}
	while (i < an)
		arts[idx++] = a[i++];
	while (j < bn)
		arts[idx++] = b[j++];
}

void merge_sort(struct s_art **arts, int n)
{
	int mid, i;
	if (n < 2)
		return ;
	mid = n / 2;
	struct s_art *a[mid], *b[n - mid];
	i = -1;
	while (++i < mid)
		a[i] = arts[i];
	i = mid - 1;
	while (++i < n)
		b[i - mid] = arts[i];
	merge_sort(a, mid);
	merge_sort(b, n - mid);
	merge(a, mid, b, n - mid, arts);
}

int	len(struct s_art **arts)
{
	int count = 0;
	while (*arts++)
		count++;
	return count;
}

void sortArts(struct s_art **arts)
{
	// bubble(arts);
	if (arts)
		merge_sort(arts, len(arts));
}