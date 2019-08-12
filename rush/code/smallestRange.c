/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallestRange.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:49:19 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/26 23:51:27 by smbaabu          ###   ########.fr       */
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

struct s_range getRange(struct s_array **arrays, int k, int *indexes)
{
    struct s_range range;
    int value;
    range.min = INT_MAX; range.max = INT_MIN;
    for (int i = 0; i < k; i++)
    {
        value = arrays[i]->arr[indexes[i]];
        if (value < range.min)
            range.min = value;
        if (value > range.max)
            range.max = value;
    }
    return (range);
}

int getSmallest(struct s_array **arrays, int k, int *indexes)
{
    int idx = -1;
    int small = INT_MAX;
    int value;
    for (int i = 0; i < k; i++)
    {
        value = arrays[i]->arr[indexes[i]];
        if (value < small) {
            small = value;
            idx = i;
        }
    }
    if (indexes[idx] == arrays[idx]->n - 1)
        return (-1);
    return (idx);
}

struct s_range smallestRange2(struct s_array **arrays, int k)
{
    int indexes[k];
    struct s_range current;
    struct s_range small;
    int idx;

    memset(indexes, 0, sizeof(int) * k); // initialize the smallest range
    small = getRange(arrays, k, indexes);
    while ((idx = getSmallest(arrays, k, indexes)) != -1)
    {
        // move on to the next element in the array which contains the minimum element
        indexes[idx]++;
        print_arr(indexes, k);
        // get the new range
        current = getRange(arrays, k, indexes);
        print_range(current);
            // update the smallest range if necessary
        if (current.max - current.min < small.max - small.min)
        {
            small.min = current.min;
            small.max = current.max;
        }
        print_range(small);
    }
    return (small);
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
    struct s_range res = smallestRange2(arrays_copy, k);
    print_range(res);
}