/*
#
#   Name: 			Eric Rouse
#   Email Address:	rousee@onid.orst.edu
#   Class Name:		CS311-400
#   Assignment:		Homework #4
#
*/
/*  toc, -t, print table of contents
    expects:
        archive_name = the name (and path) of the archive we are printing
    
    returns:
        nothing, the toc is printed
*/
#include "functions.h"

void toc(char * archive_name){
    /*vars*/
    int i;
    int fd = is_archive(archive_name);
    int size = BLOCKSIZE;
    char buf[BLOCKSIZE];
    char name[16];
    int name_idx;
    int file_ptr;
    int file_end;
    int fnd_newline = 1;
    int fnd_slash = 0;
    /*find the end of the file*/
    file_end = lseek(fd, -1, SEEK_END);
    /*set the pointer to the beginning of the file*/
    file_ptr = lseek(fd, 0, SEEK_SET);
    /*meat and potatoes*/
    while(file_ptr < file_end ){
        /*read the file, one byte at a time*/
        read(fd, buf, size);
        /*we found the file name!!!*/
        if (fnd_slash){
            write(STDOUT_FILENO, name, name_idx+1);
            fnd_newline = 0;
            fnd_slash = 0;
            name_idx = 0;   
        }
        /*check for newline*/
        if (buf[0] == '\n'){
            fnd_newline = 1;
            name_idx = 0;
            fnd_slash = 0;
        }
        /*check for slash*/
        if (buf[0] == '/' && fnd_newline){
            fnd_slash = 1;
        }
        /*if we found a newline and are still before the slash, record the name*/
        if (fnd_newline && !fnd_slash && name_idx <= sizeof(name) && buf[0] != '\n'){
            name[name_idx] = buf[0];
            name[name_idx+1] = '\n';
            name_idx++;
            
        }
        /*if we go past the index without finding the slash, we are not on a good line*/
        if (name_idx > sizeof(name)){
            name_idx = 0;
            fnd_newline = 0;
            for(i = 0; i < sizeof(name); i++) name[i] = '\0';
        } 
        /*increment to the next byte*/
        file_ptr = lseek(fd, 0, SEEK_CUR);
    }
    close(fd);
    return;
}
