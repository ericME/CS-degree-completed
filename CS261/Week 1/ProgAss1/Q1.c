/* CS261- Assignment 1 - Q.1*/
/* Name: Eric Rouse
 * Date: 10/6/2012
 * Solution description:
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>
#include<time.h>
#define NUM_STUDENTS 10

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student* p = malloc(NUM_STUDENTS*sizeof(struct student));
     assert(p != 0);
     /*return the pointer*/
     return p;
}

void generate(struct student* students){
     /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
     srand((unsigned)time(NULL)); //seed the random number generator
     //work through all the students assigning scores and id#s
     for(int i = 0; i < NUM_STUDENTS; i++){
    	 int dup = 0; //use to tell if a duplicate has been found or not.
    	 int testID = rand()%NUM_STUDENTS + 1; //assign a random number between 1 and 10 (inclusive)
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

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	//loop through each student for each id to print them in order
	for(int i = 1; i <= NUM_STUDENTS; i++){
		for(int j = 0; j < NUM_STUDENTS; j++){
			if (i == students[j].id){
				printf("ID%d Score%d\n",students[j].id, students[j].score);
				break;
			}
		}

	}

}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
     int minimum = 100;
     int maximum = 0;
     int average = 0;
     
     for(int i = 0; i < NUM_STUDENTS; i++){
    	 if(students[i].score <= minimum) minimum = students[i].score;
    	 if(students[i].score >= maximum) maximum = students[i].score;
    	 average += students[i].score;
     }
     average /= NUM_STUDENTS;
     printf("Minimum score: %d; Maximum score: %d; Average score: %d\n", minimum, maximum, average);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	assert(stud != 0);
	free(stud);
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate();
    /*call generate*/
    generate(stud);
    /*call output*/
    output(stud);
    /*call summary*/
    summary(stud);
    /*call deallocate*/
    deallocate(stud);

    return 0;
}
