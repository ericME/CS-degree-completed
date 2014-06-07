/*
#
#   Name:           Eric Rouse
#   Email Address:  rousee@onid.orst.edu
#   Class Name:     CS311-400
#   Assignment:     Homework #5
# used http://stackoverflow.com/questions/7281894/how-do-i-chain-stdout-in-one-child-process-to-stdin-in-another-child-in-c
# for an example
*/

#include "functions.h"
void set_read(int* lpipe){
/*pipe in*/
    if (close(lpipe[WRITEND])==-1){ /*close write end of pipe in*/
        perror("f2 in close");
        exit(EXIT_FAILURE);
    }

    /*connect pipe out to std in and close the duplicate*/
    if(lpipe[READEND] != STDIN_FILENO){
        if(dup2(lpipe[READEND], STDIN_FILENO) == -1){
            perror("f2 in dup2");
            exit(EXIT_FAILURE);
        }
        if(close(lpipe[READEND]) == -1){
            perror("f2 in close after dup2");
            exit(EXIT_FAILURE);                    
        }
    }
}
void set_write(int* rpipe){
    if (close(rpipe[READEND])==-1){ /*close read end*/
        perror("set_write close");
        exit(EXIT_FAILURE);
    }
    /*connect pipe out to std out and close the duplicate*/
    if (rpipe[WRITEND] != STDOUT_FILENO){
        if (dup2(rpipe[WRITEND], STDOUT_FILENO) == -1){
            perror("set_write dup2");
            exit(EXIT_FAILURE);
        }
        if (close(rpipe[WRITEND]) == -1){
            perror("set_write outpipe close");
            exit(EXIT_FAILURE);
        }
    }
}


void fork_and_chain(int* lpipe, int* rpipe, int function, char * filename)
{
    if(!fork())
    {
        if(lpipe) /*there's a pipe from the previous process*/
            set_read(lpipe);
        if(rpipe) /*there's a pipe to the next process*/
            set_write(rpipe);
        /*swithc depending on what function we are running*/
        switch (function){
            case 1:
                execlp("rev", "rev", (char*)NULL);
            case 2:
                execlp("sort", "sort", (char*)NULL);
            case 3:
                execlp("uniq", "uniq","-c", (char*)NULL);           
            case 4:
                execlp("tee", "tee", filename, (char*)NULL);
            case 5:
                execlp("wc", "wc", (char*)NULL);
            default:
                return;
        }
    }
}
void myfork(char* filename, int verbose)
{

    int i;
    /*two pipes: one from the previous in the chain, one to the next in the chain*/
    int lpipe[2], rpipe[2];

    /*create the first output pipe*/
    pipe(rpipe);

    /*first child takes input from somewhere else*/
    fork_and_chain(NULL, rpipe, 1, NULL);

    /*output pipe becomes input for the next process.*/
    lpipe[0] = rpipe[0];
    lpipe[1] = rpipe[1];

    /*chain all but the first and last children*/
    for(i = 2; i <= 4; i++)
    {
        pipe(rpipe); /*make the next output pipe*/
        fork_and_chain(lpipe, rpipe, i, filename);
        close(lpipe[0]); /*both ends are attached, close them on parent*/
        close(lpipe[1]);
        lpipe[0] = rpipe[0]; /*output pipe becomes input pipe*/
        lpipe[1] = rpipe[1];
    }

    /*fork the last one, its output goes somewhere else */     
    fork_and_chain(lpipe, NULL, 5, NULL);
    close(lpipe[0]);
    close(lpipe[1]);
    
    exit(EXIT_SUCCESS);
}
/*MAIN*/
int main(int argc, char ** argv){
    /* init vars */
    char c;
    int v = 0;
    /*
       use getopt to parse command line options
       pull in the options from the command line
       convert the numbers to longs using strtol
       acceptable options:
       -f: filename
       v, verbose mode on. v must be passed before -f as in:
       ./pipeline v -f filename, it will be ignored otherwise.
       notice that "-v" IS NOT SUPPORTED!!!!!!!
    */
    while ((c = getopt (argc,argv,"f:v"))!= -1)
        switch (c){
            case 'f':
                if(strcmp(argv[1], "v") == 0) v = 1;
                myfork(argv[optind-1], v);
                exit(EXIT_SUCCESS);
            case 'v':
                printf("verbose mode turned on, but -f not spec'd\n");
                exit(EXIT_SUCCESS);
            case '?':
                printf("******error******\n");
            default:
                printf("bad input detected\n");
                exit(EXIT_FAILURE);
        }
    
    
    
    exit(EXIT_SUCCESS);
}