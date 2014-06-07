/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	char c = ' ';
	int ret_val = 0;
	struct DynArr* stack = newDynArr(10);
	assert(stack != 0);
	assert(s != 0);
	while (c != '\0'){
		ret_val = 1;
		c = nextChar(s);

		if (c == '(' || c == '[' || c == '{') pushDynArr(stack,c);
		if (c == ')' || c == ']' || c == '}') {
			if (c == ')' && topDynArr(stack) == '(') popDynArr(stack);
			else if (c == ']' && topDynArr(stack) == '[') popDynArr(stack);
			else if (c == '}' && topDynArr(stack) == '{') popDynArr(stack);
			else return 0;
		}
	}
	if (ret_val) ret_val = !(isEmptyDynArr(stack));
	printf("return value %d\n", ret_val);
	deleteDynArr(stack);
	return ret_val;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

