#include <stdio.h>
#include <stdlib.h>
#include "linkedListQueue.h"

int main (int argc, const char * argv[]) {

    struct ListQueue *myQueue;


	myQueue =  createListQueue();


	addBackListQueue(myQueue, 0);
	addBackListQueue(myQueue, 1);
	addBackListQueue(myQueue, 2);
	addBackListQueue(myQueue, 3);
	removeFrontListQueue(myQueue);
	removeFrontListQueue(myQueue);


	return(0);

}
