/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 22:17:45 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/12 01:15:20 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

size_t hash(char *input)
{
    size_t sum = 0;

    if (!input)
        return 0;
    while (*input)
        sum += *input++;
    return sum;
}

struct s_item *create_item(char *key, int value)
{
    struct s_item *new;

    new = malloc(sizeof(struct s_item));
    new->key = key;
    new->value = value;
    new->next = NULL;
    return new;
}

struct s_dict *dictInit(int capacity)
{
    struct  s_dict *dict;
    struct s_item **items;

    if (capacity <= 0)
        return NULL;

    dict = malloc(sizeof(struct s_dict));
    items = malloc(sizeof(struct s_item) * capacity);
    dict->capacity = capacity;
    dict->items = items;
    while (--capacity >= 0)
        items[capacity] = NULL;
    return dict;
}

int	dictInsert(struct s_dict *dict, char *key, int value)
{
    struct s_item *elem, *p;
    size_t h;

    if (!dict || !dict->items || !dict->capacity || !key) // NULL values OK
        return 0;
    elem = create_item(key, value);
    h = hash(key) % dict->capacity;
    if ((p = dict->items[h]))
    {
        while (p->next)
            p = p->next;
        p->next = elem;
    }
    else
        dict->items[h] = elem;
    return 1;
}

int	dictSearch(struct s_dict *dict, char *key)
{
    struct s_item *p;
    size_t h;
    int c;

    if (!dict || !key)
        return -1;

    h = hash(key) % dict->capacity;
    if (dict && dict->items && (p = dict->items[h]))
    {
        while (p && (c = strcmp(p->key, key) != 0))
            p = p->next;
        return c == 0 ? h : -1;
    }
    else
        return -1;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		l;

	if (!s1 && !s2)
		return (NULL);
	l = 0;
	if (s1)
		l += strlen(s1);
	if (s2)
		l += strlen(s2);
	if ((ret = malloc(l + 1)) == NULL)
		return (NULL);
	if (s1)
		strcpy(ret, s1);
	if (s2)
		strcat(ret, s2);
	return (ret);
}


size_t len_words(struct s_dict *dict, size_t *no, char **words)
{
    int capacity;
    size_t sum, idx;
    struct s_item *item;

    capacity = dict->capacity;
    sum = idx = 0;
    while (--capacity >= 0)
    {
        if ((item = (dict->items)[capacity]))
        {
            while (item)
            {
                sum += strlen(item->key);
                words[idx++] = item->key;
                item = item->next;
            }
        }
    }
    *no = idx;
    return sum;
}

char    *header(char **words, size_t wlen, size_t no)
{
    char *res;
    size_t i, n, idx;

    res = malloc(wlen + no - 1 + 2 + 1);
    res[0] = '<';
    i = 1;
    idx = -1;
    while (++idx < no)
    {
        n = strlen(words[idx]);
        strncpy(res + i, words[idx], n);
        if (idx + 1 < no)
            res[i++ + n] = ',';
        i += n;
    }
    res[i++] = '>';
    res[i] = 0;
    return res;
}

char *compress(char *book, struct s_dict *dict)
{
    char    *res, *word, *h, *tmp;
    size_t  wlen, no, i, j, k, hsh;
    char    *words[255];

    no = 0;
    wlen = len_words(dict, &no, words);
    h = header(words, wlen, no);
    res = malloc(strlen(book) + 1);
    i = k = 0;
    while (book[i])
    {
        if (i == 0 || (!isspace(book[i]) && i > 1 && isspace(book[i - 1])))
        {
            j = i;
            while (!isspace(book[j]))
                j++;
            word = strndup(book + i, j);
            if ((hsh = dictSearch(dict, word)) != -1)
            {
                res[k++] = '@';
                res[k++] = hsh;
            }
        }
        i++;
    }
    tmp = res;
    res = ft_strjoin(h, res);
    free(h); free(res);
    return h;
}