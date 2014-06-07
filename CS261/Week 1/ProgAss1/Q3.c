/* CS261- Assignment 1 - Q.3*/
/* Name:Eric Rouse
 * Date: 10/6/2012
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

int left;
int right;

void sort(int* number, int n){
     /*Sort the given array number , of length n*/
	// down and dirty quicksort
	// based on the public-domain C implementation by Darel Rex Finley.
	// http://alienryderflex.com/quicksort/


	#define  MAX  1000

	int  pivot, beg[MAX], end[MAX], i=0, left, right ;

	beg[0]=0;
	end[0]=n;
	while (i>=0) {
		left=beg[i];
		right=end[i]-1;
		if (left<right) {
			pivot=number[left];
			while (left<right) {
				while (number[right]>=pivot && left<right) right--;
				if (left<right) number[left++]=number[right];
				while (number[left]<=pivot && left<right) left++;
				if (left<right) number[right--]=number[left];
			}
			number[left]=pivot;
			beg[i+1]=left+1;
			end[i+1]=end[i];
			end[i++]=left;
		}
	else i--;
	}

	return;

}

void printarray(int* a, int n){
    for (int i = 0; i < n; i++){
    	printf("%d\n",a[i]);
    }
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    left = n/20;
    right = n/20;
    /*Allocate memory for an array of n integers using malloc.*/
    int* a = malloc(n*sizeof(int));
    assert (a != 0);
    /*Fill this array with random numbers, using rand().*/
    srand((unsigned)time(NULL)); //seed the random number generator
    for (int i = 0; i < n; i++){
    	a[i] = rand();
    }
    /*Print the contents of the array.*/
    printarray(a,n);
    /*Pass this array along with n to the sort() function of part a.*/
    sort(a,n);
    /*Print the contents of the array.*/    
    printf("\n");
    printarray(a,n);
    free(a);
    return 0;
}
