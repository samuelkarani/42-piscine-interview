/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimumMoves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 21:17:59 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/14 00:47:34 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "header.h"

struct s_stack *initStack()
{
	struct s_stack *s;
	s = malloc(sizeof(struct s_stack));
	s->item = NULL;
	return s;
}

void push(struct s_stack *stack, struct s_node *node)
{
	struct s_item *item, *new;

	if (!stack)
		return;
	new = malloc(sizeof(struct s_item));
	new->node = node;
	new->next = NULL;
	item = stack->item;
	stack->item = new;
	new->next = item;
}

struct s_node *pop(struct s_stack *stack)
{
	struct s_item *item;

	if (!stack || !stack->item)
		return NULL;
	item = stack->item;
	stack->item = item->next;
	return item->node;
}

struct s_node *peek(struct s_stack *stack)
{
	if (!stack || !stack->item)
		return NULL;
	return stack->item->node;
}

int isEmpty(struct s_stack *stack)
{
	return !stack->item;
}

int contains(struct s_stack *stack, struct s_node *node)
{
	struct s_item *item = stack->item;
	if (!stack || !item)
		return 0;
	while (item)
	{
		if (item->node == node)
			return 1;
		item = item->next;
	}
	return 0;
}

int minimumMoves(struct s_node *begin)
{
	// dead end contains final
	struct s_stack *stack;
	struct s_stack *lst;
	struct s_node *node;
	int smallest, count, save, n;

	if (!begin)
		return -1;
	smallest = INT_MAX;
	count = 0;
	stack = initStack();
	lst = initStack();
	push(stack, begin);
	while (!isEmpty(stack))
	{
		node = pop(stack);
		if (!node->next)
		{
			n = count - save;
			while (n-- > 0)
				pop(lst);
			count = save;
		}
		else if (node->isFinal)
		{
			if (count < smallest)
				smallest = count;
			count = save;
		}
		else if (!contains(lst, node))
		{
			push(lst, node);
			count++;
			if (node->next)
				push(stack, node->next);
			if (node->random && node->random != node->next)
			{
				push(stack, node->random);
				save = count;
			}
		}
		else
		{
		}
		
	}
	return smallest;
}