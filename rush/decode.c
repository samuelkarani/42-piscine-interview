/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:49:23 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/26 19:49:24 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char letter(char c)
{
    return c - 1 + 'a';
}

void print(char *s)
{
    while (*s)
        putchar(*s++);
    putchar('\n');
}

char *update(char *r, char a)
{
    *r = a;
    return r + 1;
}

void helper(char *s, char *r, int j)
{
    if (!*s)
    {
        *r = 0;
        print(r - j);
        return ;
    }
    helper(s + 1, update(r, letter(*s - '0')), j + 1);
    if (*(s + 1))
        helper(s + 2, update(r, letter((*s - '0') * 10 + *(s + 1) - '0')), j + 1);
}

void decode(char *s)
{
    char *r = strdup(s);
    helper(s, r, 0);
    free(r);
}

int main(void)
{
    decode("1122");
    decode("11222");
}