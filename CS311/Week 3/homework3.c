/*
Name: 			Eric Rouse
Email Address:	rousee@onid.orst.edu
Class Name:		CS311-400
Assignment:		Homework #3
*/
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define BLOCKSIZE 1

int main(int argc, char ** argv){
    /* init vars */
	char c;
	char * filename;
	int flags = 0;
	long length = 0;
	long offset1 = 0;
	long offset2 = 0;
	long end_length = 0;
	int verbose = 0;
	int elen_on = 0;
	int fd;
    char buf[BLOCKSIZE];
    int file_ptr;
    int ptr_end;
    int i;
    long file_end;
    long file_beg;
    
    /* do some error checking
       first, check for number of arguments
       then...?
    */
    if (argc < 4) {
       fprintf(stderr, "Invalid usage: %s requires -f, -l, -o and -O at a minimum.\n", argv[0]);
       exit(EXIT_FAILURE);
    }
	/*
	   use the magic getopt (really, it is so awesome) to
	   pull in the options from the command line
	   convert the numbers to longs using strtol
    */
    while ((c = getopt (argc,argv,"vf:l:o:O:e:"))!= -1)
        switch (c){
            case 'v':
            	verbose = 1;
                break;
            case 'f':
            	filename = optarg;
            	flags++;
                break;
            case 'l':
            	length = strtol(optarg, (char**)NULL, 10);
            	flags++;
                break;
			case 'o':
				offset1 = strtol(optarg, (char**)NULL, 10);
				flags++;
                break;
			case 'O':
				offset2 = strtol(optarg, (char**)NULL, 10);
				flags++;
                break;
			case 'e':
				end_length = strtol(optarg, (char**)NULL, 10);
				elen_on = 1;
                break;
            case '?':
                printf("******error******\n");
            default:
                printf("bad input detected\n");
                exit(EXIT_FAILURE);
                break;
        }
        /* do some error checking
       first, check for number of arguments
       then flags
    */
    if (argc < 4 || flags < 4) {
       fprintf(stderr, "Invalid usage: %s requires -f, -l, -o and -O at a minimum.\n", argv[0]);
       exit(EXIT_FAILURE);
    }
    /* in verbose mode, print all the entered values */
    if (verbose){
        printf("**verbose mode on**\n   filename: %s\n   len: %ld\n   o1: %ld\n   o2: %ld\n   elen: %ld\n",
    						filename, length, offset1, offset2, end_length);
	    for(i = 0; i < argc; i++){
	        fprintf(stdout, "%s ", argv[i]);
	    }
	    printf("\n");
	}
	/* open the file */
	fd = open(filename, O_RDONLY);
    if (fd == -1){
        perror("Can't open input file");
        exit(-1);
    }
    /* find the beginning and end of the file for error purposes*/
    file_beg = lseek(fd, 0, SEEK_SET);
    file_end = lseek(fd, -1, SEEK_END);
    
    /*find and print OFFSET 1*/
    file_ptr = lseek(fd, offset1, SEEK_SET);
    ptr_end = file_ptr + length;
    if ((file_ptr > file_end) || (file_ptr < file_beg) ||
            (ptr_end > file_end) || (ptr_end < file_beg)){
        printf("\n\nOffsets point outside the file.\n\nABORTING OPERATIONS\n");
        exit(EXIT_FAILURE); 
    }
    printf("\n**<offset1>\t~~//-------------------------\\\\~~\t<offset1>**\n");
    while(file_ptr < ptr_end){
        read(fd, buf, BLOCKSIZE);
        write(STDOUT_FILENO, buf, BLOCKSIZE);
        file_ptr = lseek(fd, 0, SEEK_CUR);
    }
    
    /*find and print OFFSET 2*/
    file_ptr = lseek(fd, offset2, SEEK_CUR);
    ptr_end = file_ptr + length;
    if ((file_ptr > file_end) || (file_ptr < file_beg) ||
            (ptr_end > file_end) || (ptr_end < file_beg)){
        printf("\n\nOffsets point outside the file.\n\nABORTING OPERATIONS\n");
        exit(EXIT_FAILURE); 
    }
    printf("\n**<offset2>\t~~//-------------------------\\\\~~\t<offset2>**\n");
    while(file_ptr < ptr_end){
        read(fd, buf, BLOCKSIZE);
        write(STDOUT_FILENO, buf, BLOCKSIZE);
        file_ptr = lseek(fd, 0, SEEK_CUR);
    }
    /*find and print END BYTES*/
    if(elen_on){
        end_length = -1*(end_length);
        ptr_end = lseek(fd, -1, SEEK_END);
        file_ptr = lseek(fd, end_length, SEEK_END);
        if ((file_ptr > file_end) || (file_ptr < file_beg) ||
                (ptr_end > file_end) || (ptr_end < file_beg)){
            printf("\n\nOffsets point outside the file.\n\nABORTING OPERATIONS\n");
            exit(EXIT_FAILURE); 
        }
        printf("\n**<end bytes>\t~~//-------------------------\\\\~~\t<end bytes>**\n");
        while(file_ptr < ptr_end){
            read(fd, buf, BLOCKSIZE);
            write(STDOUT_FILENO, buf, BLOCKSIZE);
            file_ptr = lseek(fd, 0, SEEK_CUR);
        }
    }
    printf("\n");
	close(fd);    
    return 0;
}
