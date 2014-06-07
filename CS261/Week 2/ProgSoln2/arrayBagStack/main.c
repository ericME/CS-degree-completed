#include <stdio.h>
#include <stdlib.h>
#include "arrayBagStack.h"

int main (int argc, const char * argv[]) {

    struct arrayBagStack *myBag;
	
	/* Why don't these work?  
	 
	 struct arrayBagStack myBag;
	 
	 or
	 
	struct arrayBagStack *myBag;
	myBag = malloc(sizeof(struct arrayBagStack));

	 Hint: How does the compiler know the size of struct arrayBag? 
	*/
	
	myBag = createArray();
	
	initArray(myBag);
	
	addArray(myBag, 1);
	addArray(myBag, 3);
	removeArray(myBag,1);

	int res = containsArray(myBag,1);
	
	if(res > 0)
		printf("Contained 1 \n");
	else printf("Did not contain a 1\n");
	
	res = containsArray(myBag, 3);
	
	if(res > 0)
		printf("Contained a 3\n");
	else printf("Did not contain 3\n");
	return(0);
	
}
