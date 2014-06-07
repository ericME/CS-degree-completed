/*
#
#   Name:           Eric Rouse
#   Email Address:	rousee@onid.orst.edu
#   Class Name:		CS311-400
#   Assignment:		Homework #4
#
*/

#include "functions.h"


/*  extract, -x, extract named members
    expects:
        files_amount = number of files to extract (if zero, extract all)
        files_start = the starting indicy of the argv array, where the file names start
        files_name = the argv array, where the file names are stored
        archive_name = the name (and path) of the archive we are extracting from
    
    returns:
        nothing, the archive is extracted
*/
void extract(int files_amount, int files_start, char ** files_name, char * archive_name){
    /*vars*/
    int i;
    int all_files = 0;
    int num_files;
    int fd = is_archive(archive_name);
    int file_fd;
    int j;
    int next;
    int file_end;
    char found_name[16];
    char mode[4];
    char size[10];
    char prev[1];
    char buf[BLOCKSIZE];
    int reading;
    int num_read;
    int num_written;
    int filemode;
    int filesize;
    int end;
    /*find the end of the file*/
    file_end = lseek(fd, -1, SEEK_END);
    /*set the pointer to the beginning of the file*/
    lseek(fd, 0, SEEK_SET);
    /*blatant errors check*/
    if (files_amount == 0){
        all_files = 1;
    }
    /*iterate through the opened archive while there are still files to search for
      or, in the case of all files, if we have yet to reach the end of the file.*/
    num_files = files_amount;
    j = find_name(fd, found_name, 0);
    reading = 0;
    num_read = 0;
    num_written = 0;
    prev[0] = 'E';
    while(num_files > 0 || all_files*(j < file_end - 1) ){
        /*iterate through the files until we find a match*/
        /*read the mode, make sure it is null terminated, convert it to a long it*/
        lseek(fd, j + 43, SEEK_SET);
        read(fd, mode, 3*BLOCKSIZE);
        mode[3] = '\0';
        filemode = strtol(mode, (char**)NULL, 8);
        /*read the file size and convert it to a long int*/
        lseek(fd, j + 48, SEEK_SET);
        read(fd, size, 10*BLOCKSIZE);
        filesize = (int)strtol(size, (char**)NULL, 10);
        for(i = 0; i < files_amount; i++){
            /*found it! creat or trunc file and turn on reading*/
            if( strcmp(found_name,files_name[i+files_start]) == 0){
                file_fd = open(found_name, O_CREAT | O_WRONLY | O_TRUNC,  filemode);
                if(file_fd == -1){
                    printf("./myar: %s: Could not extract file\n", archive_name);
                    close(file_fd);
                    exit(EXIT_FAILURE);
                }
                num_files--;
                reading = 1;
                break;
            }
        }
        /*if we aren't given a list of files we are supposed to extract them all*/
        if(all_files == 1 && found_name[0] != '\0'){
            file_fd = open(found_name, O_CREAT | O_WRONLY | O_TRUNC,  filemode);
            if(file_fd == -1){
                printf("./myar: %s: Could not extract file\n", archive_name);
                close(file_fd);
                exit(EXIT_FAILURE);
            }
            reading = 1;
        }

        /*get the next name ready*/
        next = find_name(fd, found_name, j);
        lseek(fd, j+TITLELEN, SEEK_SET);
        end = j+filesize;
        /*if we are reading we should be writing*/
        while (reading == 1 && j <= end){
            read(fd, buf, BLOCKSIZE);
            /*make sure not to copy the double endline*/
            if (prev[0] != '\n' && buf[0] != '\n') write(file_fd, buf, BLOCKSIZE);
            else if (j < end) write(file_fd, buf, BLOCKSIZE);
            
            lseek(fd, 0, SEEK_CUR);
            lseek(file_fd, 0, SEEK_CUR);
            prev[0] = buf[0];
            j++;
        }
        
        reading = 0;
        j = next;
    
    }
    close(fd);
    close(file_fd);
    return;
}
