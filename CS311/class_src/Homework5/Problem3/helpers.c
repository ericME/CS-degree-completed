/*
#
#   Name:           Eric Rouse
#   Email Address:	rousee@onid.orst.edu
#   Class Name:		CS311-400
#   Assignment:		Homework #5
#
*/

#include "functions.h"


int msgTypify(char c, int* msgTypes){
    switch (c){
        case 'a':
            return msgTypes[1];
        case 'b':
            return msgTypes[2];
        case 'c':
            return msgTypes[3];
        case 'd':
            return msgTypes[4];
        case 'e':
            return msgTypes[5];
        case 'f':
            return msgTypes[6];
        case 'g':
            return msgTypes[7];
        case 'h':
            return msgTypes[8];
        case 'i':
            return msgTypes[9];
        case 'j':
            return msgTypes[10];
        case 'k':
            return msgTypes[11];
        case 'l':
            return msgTypes[12];
        case 'm':
            return msgTypes[13];
        case 'n':
            return msgTypes[14];
        case 'o':
            return msgTypes[15];
        case 'p':
            return msgTypes[16];
        case 'q':
            return msgTypes[17];
        case 'r':
            return msgTypes[18];
        case 's':
            return msgTypes[19];
        case 't':
            return msgTypes[20];
        case 'u':
            return msgTypes[21];
        case 'v':
            return msgTypes[22];
        case 'w':
            return msgTypes[23];
        case 'x':
            return msgTypes[24];
        case 'y':
            return msgTypes[25];
        case 'z':
            return msgTypes[26];
        default:
            exit(EXIT_FAILURE);
    }


}