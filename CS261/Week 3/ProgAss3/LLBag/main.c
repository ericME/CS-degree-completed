#include "linkedList.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*Function to get number of milliseconds elapsed since program started execution*/
double getMilliseconds() {
   return 1000.0 * clock() / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]){
	if( argc != 2 ) return 0;

	struct linkedList * b = createLinkedList();

	/* Test Area Start
	printf("For starters_ front: %d, back: %d \n", frontList(b), backList(b));
	printf("empty: %d \n", isEmptyList(b));
	addFrontList(b,24);
	addFrontList(b,33);
	printf("front: %d, back: %d \n", frontList(b), backList(b));

	addBackList(b,69);
	printf("front: %d, back: %d \n", frontList(b), backList(b));

	removeBackList(b);
	printf("front: %d, back: %d \n", frontList(b), backList(b));

	removeFrontList(b);
	printf("front: %d, back: %d \n", frontList(b), backList(b));

	printf("empty: %d \n", isEmptyList(b));

	removeFrontList(b);
	printf("front: %d, back: %d \n", frontList(b), backList(b));
	printf("empty: %d \n", isEmptyList(b));

	//bag interface

	addList(b,13);
	addList(b,8);

	printf("contains (0): %d \n", containsList(b,1));
	printf("contains (1): %d \n", containsList(b,13));
	printf("contains (2): %d \n", containsList(b,8));

	removeList(b,13);
	printf("contains (0): %d \n", containsList(b,13));


	addList(b,663);
	removeList(b,8);
	printf("contains (0): %d \n", containsList(b,8));



	Test Area End */


	int n = atoi(argv[1]);/*number of elements to add*/
	int i;
	for( i = 0 ; i < n; i++)
		addList(b, (TYPE)i);/*Add elements*/
	double t1 = getMilliseconds();/*Time before contains()*/
	for(i=0; i<n; i++) 
		containsList(b, i);
	double t2 = getMilliseconds();/*Time after contains()*/
	printf("%d %g\n", n, t2-t1);
	return 0;
}
