#include <stdio.h>
#include <stdlib.h>
#include "linkedListStack.h"

int main (int argc, const char * argv[]) {

    struct LinkedList *myStack;


	myStack =  createLinkedList(3);


	pushLinkedList(myStack, 0);
	pushLinkedList(myStack, 1);
	pushLinkedList(myStack, 2);
	pushLinkedList(myStack, 3);
	popLinkedList(myStack);
	popLinkedList(myStack);


	return(0);

}
