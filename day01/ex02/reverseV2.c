/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverseV2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 19:21:07 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/12 22:40:56 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

struct s_stack *stackInit(void)
{
	struct s_stack *s = malloc(sizeof(struct s_stack));
	s->item = NULL;
	return (s);
}

void *pop(struct s_stack *stack)
{
	struct s_item *item;

	if (!stack || !stack->item)
		return NULL;
	item = stack->item;
	stack->item = item->next;
	return item->word;
}

void push(struct s_stack *stack, char *word)
{
	struct s_item *item, *new;

	if (!stack)
		return;
	new = malloc(sizeof(struct s_item));
	new->word = word;
	new->next = NULL;
	item = stack->item;
	stack->item = new;
	new->next = item;
}

void printReverseV2(struct s_node *lst)
{
	struct s_stack *s;
	char *word;
	int count;

	s = stackInit();
	while (lst)
	{
		push(s, lst->word);
		lst = lst->next;
	}
	count = 0;
	while ((word = pop(s)))
	{
		if (count++)
			printf(" ");
		printf("%s", word);
	}
}
