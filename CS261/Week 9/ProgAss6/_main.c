#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
 * findinstr, returns int
 * this function takes in a pointer to a string array
 * iterates through it for to find a particular char
 * It returns the first instance of the char or -1 if the char isn't found
 */
int findinstr(char * arr, char find){

	int i = 0;
	while(arr[i] != '\0'){
		if (arr[i] == find) return i;
		i++;
	}
	return -1;
}

int main (int argc, const char * argv[]) {

	char arr1[] = "Tis the season to be jolly.";
	char* arrPtr1 = arr1;

	char arr2[] = "Fa La La La La La La La";
	char* arrPtr2 = arr2;

	printf("%d \n", findinstr(arrPtr1, 'j'));
	printf("%d \n", findinstr(arrPtr2, 'F'));

}
