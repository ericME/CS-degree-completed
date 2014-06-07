/*
#
#   Name:           Eric Rouse
#   Email Address:	rousee@onid.orst.edu
#   Class Name:		CS311-400
#   Assignment:		Homework #4
#
*/

#include "functions.h"
/*  del, -d, delete named members
    expects:
        files_amount = number of files to delete (if zero, extract all)
        files_start = the starting indicy of the argv array, where the file names start
        files_name = the argv array, where the file names are stored
        archive_name = the name (and path) of the archive we are extracting from
    
    returns:
        nothing, the archive is deleted from
*/
void delete(int files_amount, int files_start, char ** files_name, char * archive_name){
    /*vars*/
    int fd = is_archive(archive_name);
    int temp_fd;
    int j;
    int next;
    int file_end;
    char found_name[16];
    char buf[BLOCKSIZE];
    int reading;
    int end;
    char size_str[10];
    int size;
    int getsize;
    /*find the end of the file*/
    file_end = lseek(fd, -1, SEEK_END);
    /*set the pointer to the beginning of the file*/
    lseek(fd, 0, SEEK_SET);
    /*blatant errors check*/
    if (files_amount == 0){
        printf("no files specified\n");
        exit(EXIT_FAILURE);
    }
    /*iterate through the opened archive while there are still files to search for
      or, in the case of all files, if we have yet to reach the end of the file.*/

    j = 0;
    reading = 1;
    size = 0;
    getsize = 0;
    /*open a temporary file to store the good stuff
    there has to be a more memory efficient way to do this?*/
    temp_fd = open("~.txt", O_CREAT | O_RDWR | O_TRUNC,  0666);
    if(temp_fd == -1){
        printf("./myar: %s: Could not delete file\n", archive_name);
        close(temp_fd);
        exit(EXIT_FAILURE);
    }
    while( j < file_end - 1) {
        /*iterate through the files until we find a match*/

        /*found it! turn off reading*/
        if( strcmp(found_name,files_name[files_start]) == 0){
            reading = 0;
        }
        /*read the file size from the title block*/
        if (getsize == 1 && reading == 1){
            lseek(fd, j + 48, SEEK_SET);
            read(fd, size_str, 10*BLOCKSIZE);
            size = (int)strtol(size_str, (char**)NULL, 10);

        }
        /*get the next name ready*/
        next = find_name(fd, found_name, j);
        lseek(fd, j, SEEK_SET);
        end = next;
        /*if we are reading we should also be writing*/
        while (reading == 1 && j < end){
            read(fd, buf, BLOCKSIZE);
            write(temp_fd, buf, BLOCKSIZE);
            lseek(fd, 0, SEEK_CUR);
            lseek(temp_fd, 0, SEEK_CUR);
            getsize = 1;
            j++;
        }

        reading = 1;
        j = next;
    }
    /*make sure we are at the end of the file*/
    lseek(temp_fd, 0, SEEK_END);
    
    /*for odd files, print two newlines. Don't do that for even files*/
    if (size % 2 != 0){
        write(temp_fd, "\n", BLOCKSIZE);
        write(temp_fd, "\n", BLOCKSIZE);
    }
    close(fd);
    /*now copy the temp file back into a new archive with the old name*/
    fd = open(archive_name, O_RDWR | O_TRUNC, 0666);
    if(fd == -1){
        printf("./myar: %s: Could not copy file\n", archive_name);
        close(fd);
        exit(EXIT_FAILURE);
    }
    file_end = lseek(temp_fd, -1, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    lseek(temp_fd, 0, SEEK_SET);
    for(j = 0; j <= file_end ; j++){
        read(temp_fd, buf, BLOCKSIZE);
        write(fd, buf, BLOCKSIZE);
        lseek(fd, 0, SEEK_CUR);
        lseek(temp_fd, 0, SEEK_CUR);
    }
    close(fd);
    close(temp_fd);
    return;
}

