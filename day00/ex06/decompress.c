/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompress.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 16:07:29 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/27 20:16:33 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

static void exitError(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

static void printString(struct s_string *s)
{
	printf("%s\n", s->content);
}

static void printOccurrence(struct s_list *lst)
{
	struct s_elem *elem;
	int i = 0;
	while (i < lst->len)
	{
		elem = lst->elems[i];
		printf("%s appears %d\n", elem->word, elem->occurence);
		i++;
	}
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

static struct s_elem *create(char *s)
{
	struct s_elem *res = malloc(sizeof(struct s_elem));
	res->word = s;
	res->occurence = 0;
	return res;
}

#define INIT_SIZE 5

struct s_string *stringInit(void)
{
	struct s_string *res = malloc(sizeof(struct s_string));
	res->content = malloc(INIT_SIZE * sizeof(char));
	if (!res->content)
		return NULL;
	res->length = 0;
	res->capacity = INIT_SIZE;
	return res;
}

int	stringAppend(struct s_string *s, char *add) //return 0 = FAIL, 1 = SUCCESS
{
	char *content;
	int len, size;

	len = strlen(add);
	size = s->length + len + 1;
	if (len + 1 > s->capacity)
	{
		if (!(content = malloc(sizeof(char) * size * 2)))
			return 0;
		strncpy(content, s->content, s->length);
		strcpy(content + s->length - 1, add);
		free(s->content);
		s->content = content;
		s->length = size;
		s->capacity = size * 2;
	}
	else
	{
		strcpy(s->content + s->length, add);
		s->length = size;
	}
	return 1;
}

void appendWrapper(struct s_string *s, char *word)
{
	char *msg;

	if (!stringAppend(s, word))
	{
		asprintf(&msg, "failed to append %s ", word);
		exitError(msg);
	}
}

char *getWord(struct s_list *lst, int idx)
{
	if (!lst || !lst->elems || idx < 0 || idx >= lst->len)
		return NULL;
	struct s_elem *elem = lst->elems[idx];
	elem->occurence++;
	return elem->word;
}

struct s_list *getWordList(char *words, int l, int n)
{
	int i, end, idx, start;
	char *s;
	struct s_list *res;

	res = malloc(sizeof(struct s_list));
	res->elems = malloc(sizeof(char *) * n);
	res->len = n;
	i = start = idx = 0;
	while (i < l)
	{
		if (isalpha(words[i]) && i > 0 && words[i - 1] == ',')
			start = i;
		if (words[i] == ',' || (end = i + 1 == l))
		{
			s = fstrsub(words, start, i + end - start);
			res->elems[idx++] = create(s);
		}
		i++;
	}
	return res;
}

char *decompress(char *cBook)
{
	struct s_list *wordsList;
	size_t i;
	int start, n, index;
	struct s_string *s;
	char *word;

	i = 0;
	while (cBook[i] && cBook[i] != '<')
		i++;
	start = i + 1;
	n = 1;
	while (cBook[i] && cBook[i] != '>')
	{
		if (cBook[i] == ',')
			n++;
		i++;
	}
	wordsList = getWordList(cBook + start, i - start, n);
	printOccurrence(wordsList);
	s = stringInit();
	i++;
	while (cBook[i])
	{
		start = i;
		while (cBook[i] && cBook[i] != '@')
			i++;
		word = fstrsub(cBook, start, i - start);
		appendWrapper(s, word);
		if (cBook[i] == '@')
		{
			index = cBook[++i];
			word = getWord(wordsList, index - 1);
			if (!word)
				exitError("word not found");
			appendWrapper(s, word);
		}
		else
			break ;
		i++;
		printString(s);
	}
	printOccurrence(wordsList);
	return s->content;
}
