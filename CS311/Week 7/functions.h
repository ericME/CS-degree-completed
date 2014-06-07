/*
#
#   Name:           Eric Rouse
#   Email Address:  rousee@onid.orst.edu
#   Class Name:     CS311-400
#   Assignment:     Homework #5
#
*/

#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <ctype.h>
#include "linkedlist.h"

#define BLOCKSIZE 1
#define MXSTRGLEN 100
#define MAXARRLEN 50




/*protoypes*/
void parser(int numforks);
void sort(int max, char strings[MAXARRLEN][MXSTRGLEN]);

/*functions*/
/*
PARSER:
parses standard in into words that it puts on std ourt
based on stack overflow code
http://stackoverflow.com/questions/18109458/read-from-a-text-file-and-parse-lines-into-words-in-c
*/
void parser(int numforks){
    int c;
    int i = 0;
    int j = 0;
    int found_word = 0;
    char s[MAXARRLEN][MXSTRGLEN];

    while ((c =fgetc(stdin)) != EOF )
    {
        /*if it's an alpha, convert it to lower case*/
        if (isalpha(c))
        {
            found_word = 1;
            c = tolower(c);
            /*fputc(c, stdout);*/
            s[i][j] = c;
            j++;
        }
        else {
            if (found_word) {
                /*fputc('\n', stdout);*/
                s[i][j] = '\0';
                i++;
                j=0;
                found_word=0;
            }
        }
        if (i == MAXARRLEN){
            sort(i, s);
            i = 0;
        }

    }
    if (s != NULL) sort(i,s);
    return;

}
/*
SORT:
takes an array of strings and sorts them
very crude, very expensive
*/
void sort(int max, char strings[MAXARRLEN][MXSTRGLEN]){
    int i, j;
    char temp[MXSTRGLEN];
    /*printf ("%s, %s, %s, %s, %s\n", strings[0], strings[1], strings[2], strings[3], strings[4]);*/
    for(i=0; i < max-1 ; i++){
        for(j=i+1; j < max; j++)
        {
            if(strcmp(strings[i],strings[j]) > 0)
            {
                strcpy(temp,strings[i]);
                strcpy(strings[i],strings[j]);
                strcpy(strings[j],temp);
            }
        }
    }

    for (i = 0; i < max; i++){
        printf("%s\n", strings[i]);
    }
    return;
}



#endif