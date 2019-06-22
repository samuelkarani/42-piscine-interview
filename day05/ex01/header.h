#ifndef HEADER_H
# define HEADER_H

/*--------------------------------
  !! required structure
  --------------------------------*/
struct s_prices
{
	double *items;
	int length;
};

/*--------------------------------
  :) function you must implement
  --------------------------------*/
double bestPrice(int pizzaSize, double *prices);

/*--------------------------------
  ?? test function used in main 
  --------------------------------*/

// PARSING

struct s_prices *readList();

/*--------------------------------
  &  your own other function
  --------------------------------*/
struct s_array {
	int *content;
	int length;
	int sum;
	int capacity;
};

struct s_array *arrayInit(void);
int     arrayAppend(struct s_array *arr, int number);
struct s_array *arrayClone(struct s_array *arr);
void    arrayPrint(struct s_array *arr);
double	arrayPrice(struct s_array *arr, double *prices);

#endif
