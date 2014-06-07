/*
#
#   Name:           Eric Rouse
#   Email Address:	rousee@onid.orst.edu
#   Class Name:		CS311-400
#   Assignment:		Homework #4
#
*/

#include "functions.h"

/*  findOrCreate_archive, checks a file for existance, then if it is an archive
    if it doesn't exist a new one is created
    this is different the the is_archive function that all others use
    expects:
        archive_name = the name (and path) of the archive we are creating
    
    returns:
        file descritor for file exist and is an archive.
        0 for all else.
*/
int findOrCreate_archive(char * archive_name){
    /*vars*/
    char buf[7];
    int fd = open(archive_name, O_RDWR | O_APPEND);
    int i;
    /*blatant errors check*/
    if(fd == -1){
        /*archive doesn't exist, create it*/
        close(fd);
        printf("./myar: creating %s\n", archive_name);
        fd = open(archive_name, O_CREAT | O_WRONLY, 0666);
        if (fd == -1){
            perror("Can't create archive file");
            exit(EXIT_FAILURE);
        }
        write(fd, "!<arch>\n", sizeof("!<arch>\n"+1));
        return fd;
    }
    for (i = 0; i <= 7; i++) buf[i] = '\0';
    read(fd, buf, 7);
    if (strcmp(buf, "!<arch>") != 0){
        printf("./myar: %s: File format not recognized\n", archive_name);
        close(fd);
        exit(EXIT_FAILURE);
    }
    /*  if we made it through the errors, it is an archive.
        pass the file descriptor please */
    return fd;
}
/*  quick add, -q, quickly append named members
    expects:
        files_amount = number of files to add
        files_start = the starting indicy of the argv array, where the file names start
        files_name = the argv array, where the file names are stored
        archive_name = the name (and path) of the archive we are creating
    
    returns:
        nothing, the archive is created
*/
void quick_add(int files_amount, int files_start, char ** files_name, char * archive_name){
    /*vars*/
    int i;
    int arch_fd = findOrCreate_archive(archive_name);
    int file_fd;
    int copied;
    int file_size;
    char buf[BLOCKSIZE];
    char title_name[TITLELEN];
    int num_read;
    int num_written;
    
    /*blatant errors check*/
    if (files_amount == 0){
        printf("no files specified\n");
        exit(EXIT_FAILURE);
    }
    /*meat and potatoes*/
    
    for(i = 0; i < files_amount; i++){
        /*open the files, lseek to the beginnings; init vars*/
        file_fd = open(files_name[i+files_start], O_RDONLY);
        if (file_fd == -1){
            perror("Can't open input file");
            exit(EXIT_FAILURE);
        }
        
        file_size = lseek(file_fd, -1, SEEK_END);
        lseek(file_fd, 0, SEEK_SET);
        title(files_name[i+files_start], title_name);
        write(arch_fd, title_name, TITLELEN);
        copied = 0;
        /*copy in the file*/
        while (copied < file_size){
        
            num_read = read(file_fd, buf, BLOCKSIZE);
            
            if (num_read > 0){
                num_written = write(arch_fd, buf, BLOCKSIZE);
            }else{
                num_written = 0;
                break;
            }
            
            if (num_written != num_read || 0){
                printf("bytes written: %i\tbytes read: %i\n", num_written, num_read);
                perror("Error reading file or writing archive");
                exit(EXIT_FAILURE);
            }
        
            copied += num_written;

            
            lseek(file_fd, 0, SEEK_CUR);
            lseek(arch_fd, 0, SEEK_CUR);
            
        }
        /*make sure that odd file sizes have an extra newline to align them to even bytes*/
        write(arch_fd, "\n", BLOCKSIZE);
        if (copied % 2 == 0) write(arch_fd, "\n", BLOCKSIZE); 
        close(file_fd);
    }
    close(arch_fd);
    return;
}

