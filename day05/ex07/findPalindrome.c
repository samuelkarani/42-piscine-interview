/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findPalindrome.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 00:29:37 by smbaabu           #+#    #+#             */
/*   Updated: 2019/08/05 00:29:38 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "header.h"

char *isPalindrome(char *sequence, int l)
{
	for (int i = 0; i < l; i++)
		if (sequence[i] != sequence[l - i - 1])
			return NULL;
	return sequence;
}

void delete(char *sequence, int l, int i)
{
	memmove(sequence + i, sequence + i + 1, l - i - 1);
	sequence[l - 1] = 0;
}

void add(char *sequence, int l, int i, char c)
{
	memmove(sequence + i + 1, sequence + i, l - i - 1);
	sequence[i] = c;
	sequence[l] = 0;
}

char *helper(char *sequence, int nDelete)
{
	int l = strlen(sequence);
	if (nDelete == 0)
		return isPalindrome(sequence, l);
	char  *res, *s = strdup(sequence);
	for (int i = 0; sequence[i]; i++)
	{
		delete(s, l, i);
		if ((res = helper(s, nDelete - 1)))
			return res;
		add(s, l, i, sequence[i]);
	}
	return 0;
}

char *findPalindrome(char *sequence, int nDelete)
{
	if (sequence && nDelete > 0)
		return helper(sequence, nDelete);
	return sequence;
}
