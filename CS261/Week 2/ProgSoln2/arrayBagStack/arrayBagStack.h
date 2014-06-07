/*
 *  arrayBagStack.h
 *  arrayBagStack
 *
 *  Copyright 2010 Oregon State Univ. All rights reserved.
 *
 */

# ifndef ArrayBagStack
# define ArrayBagStack

# define TYPE int
# define EQ(a, b) (a == b)

/* prototype for the struct, which is hidden away in the .c file */
struct arrayBagStack;

/* Bag Interface */
struct arrayBagStack *createArray();
void initArray (struct arrayBagStack * b);
void addArray (struct arrayBagStack * b, TYPE v);
int containsArray (struct arrayBagStack * b, TYPE v);
void removeArray (struct arrayBagStack * b, TYPE v);
int sizeArray (struct arrayBagStack * b);

/* Stack Interface */
void pushArray (struct arrayBagStack * b, TYPE v);
TYPE topArray (struct arrayBagStack * b);
void popArray (struct arrayBagStack * b);
int isEmptyArray (struct arrayBagStack * b);

# endif

