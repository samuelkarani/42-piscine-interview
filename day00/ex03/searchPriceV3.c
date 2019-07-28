/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchPriceV3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:36:40 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/26 18:46:50 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
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

struct s_item *create_item(char *key, struct s_art *value)
{
    struct s_item *new;

    new = malloc(sizeof(struct s_item));
    new->key = key;
    new->value = value;
    new->next = NULL;
    return new;
}

int	dictInsert(struct s_dict *dict, char *key, struct s_art *value)
{
    struct s_item *elem, *p;
    size_t h;

    if (!dict || !dict->items || dict->capacity <= 0 || !key) // NULL value OK
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

struct s_art *dictSearch(struct s_dict *dict, char *key)
{
    struct s_item *p;
    size_t h;
    int c;

    if (!dict || !key)
        return NULL;

    h = hash(key) % dict->capacity;
    if (dict && dict->items && (p = dict->items[h]))
    {
        while (p && (c = strcmp(p->key, key) != 0))
            p = p->next;
        return c == 0 ? p->value : NULL;
    }
    else
        return NULL;
}

int searchPrice(struct s_dict *dict, char *name)
{
    struct s_art *found;

    if (!dict || !name)
        return -1;

    if ((found = dictSearch(dict, name)))
        return found->price;
    return -1;
}
