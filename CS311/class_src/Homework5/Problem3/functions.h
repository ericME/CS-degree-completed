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
#define MAXFORKS 26




/*protoypes*/
int msgTypify(char c, int* msgList);
void sigi_handler(int sig);



#endif