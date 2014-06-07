#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

/*printmap prototype*/
/* Prints all of the map, array by array, link by link */
void printMap(struct hashMap * ht);

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file);

int main (int argc, const char * argv[]) {
    const char* filename;
    struct hashMap hashTable;
    int tableSize = 997;
	clock_t timer;
    
    /*
     this part is using command line arguments, you can use them if you wish
     but it is not required. DO NOT remove this code though, we will use it for
     testing your program.
     
     if you wish not to use command line arguments manually type in your
     filename and path in the else case.
     */
    if(argc == 2)
        filename = argv[1];
    else
        filename = "input.txt"; /*specify your input text file here*/
    
    printf("opening file: %s\n", filename);
    
	timer = clock();
	
    initMap(&hashTable, tableSize);
    
    /*
     Concordance Code
     */

    //open the file and initialize the word
    FILE * file = fopen(filename,"r");
    KeyType word = (KeyType)getWord(file);

    //if word is not null, iterate through all the words in the file.
    while(word != NULL){
    	int * count;
    	//if the word is found, increase the count by 1
    	if (containsKey(&hashTable, word) == 1){
    		count = atMap(&hashTable, word);
    		*count += 1;
    	}
    	//otherwise insert a new word with a count of 1
    	else insertMap(&hashTable, word, 1);
    	//iterate
    	word = getWord(file);
    }

    printf("\n\n"); //throw some spaces in
    fclose(file);

    //print the whole map
    printMap(&hashTable);



    /*test cases for debug*/
    /*
    insertMap(&hashTable, "sevne", 7);
    insertMap(&hashTable, "seevn", 4);
    insertMap(&hashTable, "seven", 6);
    insertMap(&hashTable, "sveen", 5);
    printMap(&hashTable);
    printf("Size: %d\n", size(&hashTable));
    printf("contains: %d \n", containsKey(&hashTable, "seven"));
    printf("contains: %d \n", containsKey(&hashTable, "notaword"));
    int digits = atMap(&hashTable, "seven");
    printf("atMap: %d %d \n", atMap(&hashTable, "seven"), digits);

    removeKey(&hashTable, "seven");
    printf("removed seven: %d \n", containsKey(&hashTable, "seven"));

    removeKey(&hashTable, "seven");
    printf("Size: %d\n", size(&hashTable));
    printMap(&hashTable);
    */


	timer = clock() - timer;
	printf("concordance ran in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    
    return 0;
}

char* getWord(FILE *file)
{
	int length = 0;
	int maxLength = 16;
	char character;
    
	char* word = (char*)malloc(sizeof(char) * maxLength);
	assert(word != NULL);
    
	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if(character >= '0' && character <= '9' || /*is a number*/
		   character >= 'A' && character <= 'Z' || /*or an uppercase letter*/
		   character >= 'a' && character <= 'z' || /*or a lowercase letter*/
		   character == 39) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
			break;
	}
    
	if(length == 0)
	{
		free(word);
		//printf("got to null!!"); //debug
		return NULL;
	}
	word[length] = '\0';
	return word;
}
