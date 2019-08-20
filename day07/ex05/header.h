#ifndef HEADER_H
# define HEADER_H

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*--------------------------------
  !! required structure
  --------------------------------*/


/*--------------------------------
  :) function you must implement
  --------------------------------*/

char *neverForget(char *words, char **dictionary);


/*--------------------------------
  ?? test function used in main
  --------------------------------*/

extern char *g_dict[];

char *get_content(char *file);


/*--------------------------------
  &  your own other function
  --------------------------------*/

struct s_word
{
	char *word;
	int len;
	struct s_word *next;
};

#endif
