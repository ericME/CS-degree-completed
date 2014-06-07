#include <stdio.h>
#include <stdlib.h>
#include "dynamicArrayDeque.h"

int main (int argc, const char * argv[]) {

    struct DynArr *myDeque;


	myDeque =  createDynArr(3);


	addBackDynArr(myDeque, 0);
	addBackDynArr(myDeque, 1);
	addBackDynArr(myDeque, 2);
	addBackDynArr(myDeque, 3);
	removeFrontDynArr(myDeque);
	removeFrontDynArr(myDeque);
	removeBackDynArr(myDeque);

	int res = containsDynArr(myDeque,1);

	if(res > 0)
		printf("Contained 1 \n");
	else printf("Did not contain 1\n");

	res = containsDynArr(myDeque,3);
	if(res > 0)
		printf("Contained 3\n");
	else printf("Did not contain 3\n");
	return(0);

}
