/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortStone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 00:32:52 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/14 13:17:14 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

struct s_block *create_block(struct s_stone *stone)
{
    struct s_block *res = malloc(sizeof(struct s_block));
    res->size = stone->size;
    res->list = stone;
    res->next = NULL;
    return res;
}

void swap(struct s_block *a, struct s_block *b)
{
   struct s_stone *tmpl = a->list;
   int tmps = a->size;
   a->list = b->list;
   a->size = b->size;
   b->list = tmpl;
   b->size = tmps;
}

void print_blocks(struct s_block *block)
{
    struct s_stone *lst;
    while (block)
    {
        lst = block->list;
        while (lst)
        {
            printf("%d ", lst->size);
            lst = lst->next;
        }
        block = block->next;
    }
    printf("\n");
}

void sortStones(struct s_stone **stone)
{
    struct s_block *blocks, *b, *i, *j;
    struct s_stone *stones, *prev, *blks_lst, *blks, *next;

    if (!stone)
        return ;
    
    // create blocks
    stones = *stone;
    prev = NULL;
    b = blocks = create_block(stones);
    blks = blks_lst = blocks->list;
    while (stones)
    {
       if (prev)
       {
            if (stones->size != prev->size)
            {
                blocks->next = create_block(stones);
                blocks = blocks->next;
                next = blocks->list;
                blks_lst->next = NULL;
                blks_lst = next;
            }
            else
            {
                blks_lst->next = stones;
                blks_lst = blks_lst->next;
            }
       }
        prev = stones;
        stones = stones->next;
    }
    blocks->next = NULL;
    blks_lst->next = NULL;

    // print_blocks(b);
    
    // sort blocks
    i = b;
    while (i->next)
    {
        j = b;
        while (j->next)
        {
            if (j->size > j->next->size)
                swap(j, j->next);
            j = j->next;
        }
        i = i->next;
    }

    // print_blocks(b);
    
    // join blocks
    blocks = b;
    blks = blocks->list;
    while (blocks->next)
    {
        blks_lst = blocks->list;
        while (blks_lst->next)
            blks_lst = blks_lst->next;
        blocks = blocks->next;
        blks_lst->next = blocks->list;
    }

    *stone = blks;
}