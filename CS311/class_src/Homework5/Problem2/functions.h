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
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <dirent.h> 

#define BLOCKSIZE 1
#define READEND 0
#define WRITEND 1

/*prototypes*/
void myfork(char* filename, int verbose);
void fork_and_chain(int* lpipe, int* rpipe, int function, char * filename);
void set_read(int* readpipe);
void set_write(int* writepipe);


#endif