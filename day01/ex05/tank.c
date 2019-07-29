/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tank.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:12:19 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/28 16:30:14 by smbaabu          ###   ########.fr       */
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
		if ((e = s->elem))
		{
			printf("stack \033[0;33m%d\033[0m sum \033[0;32m%d\n\033[0m", i, s->sum);
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

int removeEnergy(struct s_stack *s)
{
	struct s_elem *e;
	if (!s || !s->elem)
		return -1;
	e = s->elem;
	s->elem = s->elem->next;
	s->sum -= e->energy;
	return e->energy;
}

int tankPop(struct s_tank *tank)
{
	struct s_stack *s;
	int res;

	res = -1;
	if (tank->n > 0)
	{
		s = tank->stacks[tank->n - 1];
		if (s->elem)
			res = removeEnergy(s);
		else
		{
			if (tank->n - 2 >= 0)
			{
				s = tank->stacks[tank->n - 2];
				res = removeEnergy(s);
			}
			tank->n--;
		}
	}
	return res;
}