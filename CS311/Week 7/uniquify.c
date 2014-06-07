/*
#
#   Name:           Eric Rouse
#   Email Address:  rousee@onid.orst.edu
#   Class Name:     CS311-400
#   Assignment:     Homework #5
#
*/

#include "functions.h"

int main (int argc, char **argv)
{
        /* init vars */
    char ch;
    int numforks = 1;
    int msqid;
    int c;
    int i = 0;
    int j = 0;
    int found_word = 0;
    char s[MXSTRGLEN];
    struct linkedList * master;
    master = createLinkedList();
    /*
       use getopt to parse command line options
       pull in the options from the command line
       convert the numbers to longs using strtol
       acceptable options:
       -n: number of sort forks to create
    */
    while ((ch = getopt (argc,argv,"n:"))!= -1)
        switch (ch){
            case 'n':
                numforks = (int)strtol(argv[optind-1], (char**)NULL, 10);
                break;
            case '?':
                printf("******error******\n");
            default:
                printf("bad input detected\n");
                exit(EXIT_FAILURE);
        }

    /*generate a message queue*/
    msqid = msgget(IPC_PRIVATE,S_IRUSR | S_IWUSR);
    /*make sure numforks is valid*/
    if (numforks > 50) numforks = 50;
    else if (numforks < 1) numforks = 1;
    /*fork and execs go here*/


    while ((c =fgetc(stdin)) != EOF )
    {
        /*if it's an alpha, convert it to lower case*/
        if (isalpha(c))
        {
            found_word = 1;
            c = tolower(c);
            /*fputc(c, stdout);*/
            s[j] = c;
            j++;
        }
        else {
            if (found_word) {
                /*fputc('\n', stdout);*/
                s[j] = '\0';
                i++;
                j=0;
                found_word=0;
                addBackList(master, s);
                printf("%i\t\t\t%s\t%s\t%s\n", sizeofList(master), s, backList(master), frontList(master));
            }
        }
        /*printList(master);*/
    }
    /*printf("%s", backList(master));*/
    printList(master);


    /*wait for children to finish*/
    while (wait(NULL) > 0 );
    /*kill the queue*/
    msgctl(msqid, IPC_RMID, NULL);
    exit(EXIT_SUCCESS);
}