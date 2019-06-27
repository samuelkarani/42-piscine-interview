/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallestRange.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:49:19 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/26 22:06:47 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct s_range {
    int max;
    int min;
};

struct s_array {
    int *arr;
    int n;
};

void initRange(struct s_range *range)
{
    range->max = INT_MIN;
    range->min = INT_MAX;
}

struct s_range minRange(int *arr, int n)
{
    struct s_range res;
    initRange(&res);
    while (--n >= 0)
    {
        if (arr[n] > res.max)
            res.max = arr[n];
        if (arr[n] < res.min)
            res.min = arr[n];
    }
    return res;
}

void print_arr(int *arr, int n)
{
    int i = -1;
    while (++i < n)
        printf("%d ", arr[i]);
    printf("\n");
}

void print_range(struct s_range range)
{
    printf("range: %d %d\n", range.min, range.max);
}

void helper(struct s_array **arrays, int k, int *arr, int i, struct s_range *min)
{
    int j;
    struct s_range range;

    if (i == k)
    {
        range = minRange(arr, k);
        if (min->max == INT_MIN
            || (range.max - range.min < min->max - min->min))
            memcpy(min, &range, sizeof(range));
    }
    j = -1;
    while (++j < arrays[i]->n)
    {
        arr[i] = arrays[i]->arr[j];
        helper(arrays, k, arr, i + 1, min);
    }
}

struct s_range smallestRange(struct s_array **arrays, int k)
{
    int arr[k];
    struct s_range min;
    initRange(&min);
    helper(arrays, k, arr, 0, &min);
    return min;
}

int main(void)
{
    int arr1[] = {4, 10, 15, 24, 26};
    int arr2[] = {0, 9, 12, 20};
    int arr3[] = {5, 18, 22, 30};
    struct s_array arrays[] = {
        {arr1, 5},
        {arr2, 4},
        {arr3, 4}
    };
    int k = 3;
    struct s_array **arrays_copy = malloc(sizeof(struct s_array *) * k);
    int i = -1;
    while (++i < k)
    {
        arrays_copy[i] = malloc(sizeof(struct s_array));
        memcpy(arrays_copy[i], &arrays[i], sizeof(struct s_array));
    }
    struct s_range res = smallestRange(arrays_copy, k);
    print_range(res);
}