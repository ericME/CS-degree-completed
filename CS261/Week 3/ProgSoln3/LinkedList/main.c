#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

int main (int argc, const char * argv[]) {

    struct linkedList *myStack;


	myStack =  createLinkedList(3);


	addFrontList(myStack, 0);
	addFrontList(myStack, 1);
	addFrontList(myStack, 2);
	addFrontList(myStack, 3);
	removeFrontList(myStack);
	removeFrontList(myStack);


	return(0);

}
