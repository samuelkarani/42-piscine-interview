/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 16:22:11 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/12 19:13:53 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void printReverseIterative(struct s_node *lst)
{
    struct s_node *next;
    struct s_node *prev;
    size_t count;

    prev = NULL;
    while (lst)
    {
        next = lst->next;
        lst->next = prev;
        prev = lst;
        lst = next;
    }
    count = 0;
    while (prev)
    {
        if (count)
            printf(" ");
        printf("%s", prev->word);
        prev = prev->next;
        count++;
    }
}

void helper(struct s_node *lst, int n)
{
    if (!lst)
        return;
    helper(lst->next, n + 1);
    printf("%s", lst->word);
    if (n)
        printf(" ");
}

void printReverse(struct s_node *lst)
{
    helper(lst, 0);
}