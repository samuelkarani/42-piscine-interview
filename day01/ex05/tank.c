/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tank.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:12:19 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/13 16:51:27 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "header.h"

struct s_elem *create_elem(int energy)
{
	struct s_elem *e = malloc(sizeof(struct s_elem));
	e->energy = energy;
	e->next = NULL;
	return e;
}

struct s_stack *create_stack(struct s_elem *elem, int sum)
{
	struct s_stack *s = malloc(sizeof(struct s_stack));
	s->elem = elem;
	s->sum = sum;
	return s;
}

struct s_tank *initTank(void)
{
	struct s_tank *tank = malloc(sizeof(struct s_tank));
	struct s_stack **stacks = malloc(sizeof(struct s_stack));
	tank->n = 1;
	*stacks = create_stack(NULL, 0);
	tank->stacks = stacks;
	return tank;
}

struct s_stack **addStack(struct s_stack **stacks, int oldSize, struct s_stack *new)
{
	struct s_stack **newStacks;
	newStacks = realloc(stacks, (oldSize + 1) * sizeof(struct s_stack));
	newStacks[oldSize] = new;
	return newStacks;
}

void printTank(struct s_tank *tank)
{
	struct s_stack *s;
	struct s_elem *e;
	int n, i;

	n = tank->n;
	i = 0;
	while (i < n)
	{
		s = tank->stacks[i];
		printf("stack \033[0;33m%d\033[0m sum \033[0;32m%d\n\033[0m", i, s->sum);
		if ((e = s->elem))
		{
			while (e)
			{
				printf("elem \033[0;34m%d\n\033[0m", e->energy);
				e = e->next;
			}
		}
		i++;
	}
	printf("\n");
}

void tankPush(struct s_tank *tank, int energy)
{
	struct s_stack *s;
	struct s_elem *e, *p;
	int n;

	if (!tank)
		return;
	e = create_elem(energy);
	n = tank->n;
	s = tank->stacks[n - 1];
	if (s->sum + energy < 1000)
	{
		if (!s->elem)
			s->elem = e;
		else
		{
			p = s->elem;
			s->elem = e;
			e->next = p;
		}
		s->sum += energy;
	}
	else
	{
		s = create_stack(e, energy);
		tank->stacks = addStack(tank->stacks, n, s);
		(tank->n)++;
	}
}

int tankPop(struct s_tank *tank)
{
	struct s_stack *s;
	struct s_elem *e;

	if (tank->n)
	{
		s = tank->stacks[tank->n - 1];
		if (!s->elem)
		{
			if (tank->n - 2 < 0)
				s = NULL;
			else
				s = tank->stacks[tank->n - 2];
		}
		if (s && (e = s->elem))
		{
			s->elem = e->next;
			if (!e->next)
				(tank->n)--;
			else
				s->sum -= e->energy;
			return e->energy;
		}
		else
		{
			if (tank->n)
				(tank->n)--;
			return -1;
		}
	}
	return -1;
}