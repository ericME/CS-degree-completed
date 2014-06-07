#include <stdio.h>

void fb1(int n){
	int i;
	int printed;
	for (i=1;i<=n;i++){
		if (i % 3 == 0){
			printf("fizz");
			printed++;
		}
		if (i % 5 == 0){
			printf("buzz");
			printed++;
		}
		if (printed == 0){
			printf("%i",i);
		}
		
		printf("\n");
		printed = 0;
	}
}

void fb2(int n){
	char * print[] = {"%i\n","fizz\n","buzz\n","fizzbuzz\n"};
	for (int i=1;i<=n;i++){
		printf(print[(i%3==0)+2*(i%5==0)],i);
	}
}

void main (int argc, char ** argv){

	fb2(100);

	return;
}