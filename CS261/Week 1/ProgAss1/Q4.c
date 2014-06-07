/* CS261- Assignment 1 - Q.4*/
/* Name: Eric Rouse
 * Date: 10/6/2012
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
	// down and dirty quicksort
	// based on the public-domain C implementation by Darel Rex Finley.
	// http://alienryderflex.com/quicksort/


	#define  MAX  1000
	struct student pivot;

	int beg[MAX], end[MAX], i=0, left, right ;

	beg[0]=0;
	end[0]=n;
	while (i>=0) {
		left=beg[i];
		right=end[i]-1;
		if (left<right) {
			pivot=students[left];
			while (left<right) {
				while (students[right].score>=pivot.score && left<right) right--;
				if (left<right) students[left++]=students[right];
				while (students[left].score<=pivot.score && left<right) left++;
				if (left<right) students[right--]=students[left];
			}
			students[left]=pivot;
			beg[i+1]=left+1;
			end[i+1]=end[i];
			end[i++]=left;
		}
	else i--;
	}

	return;

}

void generate(struct student* students, int n){
     /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
     srand((unsigned)time(NULL)); //seed the random number generator
     //work through all the students assigning scores and id#s
     for(int i = 0; i < n; i++){
    	 int dup = 0; //use to tell if a duplicate has been found or not.
    	 int testID = rand()%n + 1; //assign a random number between 1 and 10 (inclusive)
    	 students[i].score = rand()%101; //assign a random number between 0 and 100 (inclusive)
    	 //verify the id is not a duplicate
    	 for(int j = 0; j < i; j++){
    		 //if a dup is found, try again at the same i value
    		 if (testID == students[j].id){
    			 dup = 1;
    			 i--;
    			 break;
    		 }
    	 }
    	 if (!dup) students[i].id = testID;

     }
}

void print(struct student* students, int n){
	for (int i = 0; i < n; i++){
		printf("ID%d, Score %d\n", students[i].id, students[i].score);
	}
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 20;
    /*Allocate memory for n students using malloc.*/
    struct student* s = malloc(n*sizeof(struct student));
    /*Generate random IDs and scores for the n students, using rand().*/
    generate(s,n);
    /*Print the contents of the array of n students.*/
    print(s,n);
    /*Pass this array along with n to the sort() function*/
    sort(s,n);
    /*Print the contents of the array of n students.*/
    printf("\n");
    print(s,n);
    return 0;
}
