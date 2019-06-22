/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maxSW.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 15:47:51 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/21 19:02:13 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "header.h"

struct s_deque *dequeInit(void)
{
    struct s_deque *res = malloc(sizeof(struct s_deque));
    res->first = res->last = NULL;
    return res;
}

struct s_dequeNode *createDeque(int value)
{
    struct s_dequeNode *res = malloc(sizeof(struct s_dequeNode));
    res->value = value;
    res->prev = res->next = NULL;
    return res;
}

void pushFront(struct s_deque *deque, int value)
{
    struct s_dequeNode *first = deque->first;
    deque->first = createDeque(value);
    if (!first)
        deque->last = deque->first;
    else
    {
        deque->first->next = first;
        first->prev = deque->first;
    }
}

void pushBack(struct s_deque *deque, int value)
{
    struct s_dequeNode *last = deque->last;
    deque->last = createDeque(value);
    if (!last)
        deque->first = deque->last;
    else
    {
        deque->last->prev = last;
        last->next = deque->last;
    }
}

int peekFront(struct s_deque *deque)
{
    if (!deque->first)
        return INT_MIN;
    return deque->first->value;
}

int popFront(struct s_deque *deque)
{
    struct s_dequeNode *first = deque->first;
    if (!first)
        return INT_MIN;
    deque->first = first->next;
    if (first == deque->last)
        deque->last = NULL;
    else if (deque->first)
        deque->first->prev = NULL;
    return first->value;
}

int popBack(struct s_deque *deque)
{
    struct s_dequeNode *last = deque->last;
    if (!last)
        return INT_MIN;
    deque->last = last->prev;
    if (last == deque->first)
        deque->first = NULL;
    else if (deque->last)
        deque->last->next = NULL;
    return last->value;
}

int peekBack(struct s_deque *deque)
{
    if (!deque->last)
        return INT_MIN;
    return deque->last->value;
}

int isEmpty(struct s_deque *deque)
{
    return !deque->first;
}

struct s_max *createArr(int n)
{
    struct s_max *res = malloc(sizeof(struct s_max));
    res->length = n;
    res->max = malloc(sizeof(int) * n);
    return res;
}

struct s_max *maxSlidingWindow(int *arr, int n, int k)
{
    struct s_deque *deque;
    struct s_max *res;
    int i, idx;

    res = createArr(n - k + 1);
    deque = dequeInit();
    i = idx = 0;
    for (int i = 0; i < n; i++)
    {
        if (!isEmpty(deque) && peekFront(deque) == i - k)
            popFront(deque);
        while (!isEmpty(deque) && arr[peekBack(deque)] < arr[i])
            popBack(deque);
        pushBack(deque, i);
        if (i >= k - 1)
            res->max[idx++] = arr[peekFront(deque)];
    }
    return res;
}
