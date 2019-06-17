/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 21:34:16 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/13 19:33:21 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

struct s_stack *initStack()
{
	struct s_stack *s;

	s = malloc(sizeof(struct s_stack));
	s->item = NULL;
	return s;
}

void push(struct s_stack *stack, int idx)
{
	struct s_item *item, *new;

	if (!stack)
		return;
	new = malloc(sizeof(struct s_item));
	new->idx = idx;
	new->next = NULL;
	item = stack->item;
	stack->item = new;
	new->next = item;
}

int pop(struct s_stack *stack)
{
	struct s_item *item;

	if (!stack || !stack->item)
		return -1;
	item = stack->item;
	stack->item = item->next;
	return item->idx;
}

char *console(void)
{
	struct s_stack *s;
	char msg[256];
	int n, l;

	s = initStack();
	n = 0;
	*msg = 0;
	while (1)
	{
		printf("?: ");
		fgets(msg + n, 256 - n, stdin);
		l = strlen(msg + n) - 1;
		n += l;
		msg[n] = 0;
		if (strcmp(&msg[n - l], "UNDO") == 0)
		{
			l = pop(s);
			if (l == -1)
				l = 0;
			n = n - l - 4;
			msg[n] = 0;
		}
		else if (strcmp(&msg[n - l], "SEND") == 0)
		{
			msg[n - l] = 0;
			break;
		}
		else if (l > 0)
			push(s, l);
		puts(msg);
	}
	return strcpy(malloc(n), msg);
}