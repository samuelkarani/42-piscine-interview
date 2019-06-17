/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precious.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:01:43 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/12 17:42:48 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void print_list(struct s_node *lst)
{
	struct s_node *start = lst;
	do
	{
		printf("%c", lst->c);
		lst = lst->next;
	} while (lst != start);
	printf("\n");
}

struct s_node *create_lst(void)
{
	struct s_node *res, *p, *new;
	int i;

	res = p = malloc(sizeof(struct s_node));
	p->c = *CS;
	i = 1;
	while (CS[i])
	{
		new = malloc(sizeof(struct s_node));
		new->c = CS[i];
		p->next = new;
		new->prev = p;
		p = new;
		i++;
	}
	res->prev = p;
	p->next = res;
	return res;
}

void rotate(struct s_node **lst, int n)
{
	if (n > 0)
	{
		while (n-- > 0)
			*lst = (*lst)->next;
	}
	else if (n < 0)
	{
		while (n++ < 0)
			*lst = (*lst)->prev;
	}
}

char *precious(int *text, int size)
{
	struct s_node *lst;
	char *res;
	int i;

	lst = create_lst();
	// print_list(lst);
	res = malloc(size + 1);
	res[size] = 0;
	i = -1;
	while (++i < size)
	{
		rotate(&lst, text[i]);
		res[i] = lst->c;
	}
	return res;
}
