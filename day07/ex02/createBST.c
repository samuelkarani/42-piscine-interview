/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createBST.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 19:06:32 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/21 19:23:57 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"

struct s_node *create(int value)
{
    struct s_node *res = malloc(sizeof(struct s_node));
    res->value = value;
    res->left = res->right = NULL;
    return res;
}

struct s_node *createBST(int *arr, int n)
{
    if (n == 0)
        return NULL;
    if (n == 1)
        return create(arr[0]);
    int mid = n / 2;
    struct s_node *node = create(arr[mid]);
    node->left = createBST(arr, mid);
    node->right = createBST(arr + mid + 1, n - mid - 1);
    return node;
}