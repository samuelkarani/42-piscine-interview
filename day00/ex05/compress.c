/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 22:17:45 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/27 18:51:12 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

static struct s_item *create_item(char *key, int value)
{
    struct s_item *new;

    new = malloc(sizeof(struct s_item));
    new->key = key;
    new->value = value;
    new->next = NULL;
    return new;
}

static char	*fstrjoin(char const *s1, char const *s2)
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

static char	*fstrsub(char const *s, int start, int len)
{
	char *res = malloc(sizeof(char) * len + 1);
	int i = 0;
	while (len-- > 0)
		res[i++] = s[start++];
	res[i] = 0;
	return res;
}

size_t hash(char *str)
{
    size_t res = 5381;
    int c;
    while ((c = *str++))
        res = ((res << 5) + res) + c; /* res * 33 + c */
    return res;
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

    if (!dict || !dict->items || dict->capacity <= 0 || !key) // NULL values OK
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
        return c == 0 ? p->value : -1;
    }
    else
        return -1;
}

void len_words(struct s_dict *dict, int res[2], char **words)
{
    int size, idx, i;
    struct s_item *item;

    i = size = idx = 0;
    while (i < dict->capacity)
    {
        if ((item = (dict->items)[i]))
        {
            while (item)
            {
                size += strlen(item->key);
                words[item->value] = item->key;
                item = item->next;
				idx++;
            }
        }
		i++;
    }
    res[0] = idx;
	res[1] = size;
}

char *getHeader(char **words, int num, int size)
{
    char *res;
    int i, n, idx;

    res = malloc(size + (num - 1) + (2) + 1);
    i = 0;
    res[i++] = '<';
    idx = -1;
    while (++idx < num)
    {
        n = strlen(words[idx]);
        strncpy(res + i, words[idx], n);
        if (idx + 1 < num)
            res[i++ + n] = ',';
        i += n;
    }
    res[i++] = '>';
    res[i] = 0;
    return res;
}

char *compress(char *book, struct s_dict *dict)
{
    char *res, *word, *header;
    int strings[2], len, index;
	size_t i, start, idx;
    char *words[256];

	words[255] = NULL;
    len_words(dict, strings, words);
    header = getHeader(words, strings[0], strings[1]);
    res = malloc(strlen(book) + 1);
    i = start = idx = 0;
    while (book[i])
    {
		if (!isspace(book[i]) && i > 0 && isspace(book[i - 1]))
			start = i;
		else if ((isspace(book[i]) && i > 0 && !isspace(book[i - 1]))
			|| (!isspace(book[i]) && !book[i + 1]))
		{
			i = start;
			while (isalpha(book[i]))
				i++;
			len = i - start;
			word = fstrsub(book, start, len);
			index = dictSearch(dict, word);
            if (index != -1)
            {
                res[idx++] = '@';
                res[idx++] = index + 1;
            }
			else
			{
				strncpy(res + idx, word, len);
				idx += len;
			}
			while (book[i] && !isspace(book[i]))
				res[idx++] = book[i++];
			res[idx++] = book[i];
			if (!book[i])
				break;
		}
		else if (isspace(book[i]))
			res[idx++] = book[i];
		i++;
    }
    res = fstrjoin(header, res);
    free(header);
    return res;
}