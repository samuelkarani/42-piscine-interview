/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortArts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:52:31 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/26 15:08:01 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "header.h"

static int ascending(char *a, char *b)
{
	return strcmp(a, b) <= 0;
}

static int ascending_s(struct s_art *a, struct s_art *b)
{
	return strcmp(a->name, b->name) <= 0;
}

static int	len(struct s_art **arts)
{
	int count = 0;
	while (*arts++)
		count++;
	return count;
}

static void swap(struct s_art *a, struct s_art *b)
{
	char *name = a->name;
	int price = a->price;
	a->name = b->name;
	a->price = b->price;
	b->name = name;
	b->price = price;
}

void insertion(struct s_art **arts)
{
	struct s_art *art;
	int i = 0, hole;
	while (arts[i + 1])
	{
		hole = i + 1;
		art = arts[hole];
		while (hole > 0 && !ascending(arts[hole - 1]->name, art->name))
		{
			arts[hole] = arts[hole - 1];
			hole--;
		}
		arts[hole] = art;
		i++;
	}
}

void selection(struct s_art **arts)
{
	int i, j, idx;
	i = 0;
	while (arts[i])
	{
		idx = i;
		j = i;
		while (arts[j])
		{
			if (!ascending_s(arts[i], arts[j]))
				idx = j;
			j++;
		}
		swap(arts[i], arts[idx]);
		i++;
	}
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

void sortArts(struct s_art **arts)
{
	if (!arts || !arts[0])
		return ;
	// bubble(arts);
	// insertion(arts);
	// selection(arts);
	merge_sort(arts, len(arts));
}