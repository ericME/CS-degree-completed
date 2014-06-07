/* CS261- Assignment 1 - Q.5*/
/* Name: Eric Rouse
 * Date: 10/6/2012
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LEN 16

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/

	for (int i; i < LEN; i++){
		if (word[i] == '\0') break;
		if(i%2 == 0 && islower(word[i])) word[i] = toUpperCase(word[i]);
		else if (i%2 !=0 && isupper(word[i])) word[i] = toLowerCase(word[i]);
	}
}

int main(){
	char word[LEN];
    /*Read word from the keyboard using scanf*/
	scanf("%15s", word);
    /*Call sticky*/
    sticky(word);
    /*Print the new word*/
    printf("%s", word);
    return 0;
}
