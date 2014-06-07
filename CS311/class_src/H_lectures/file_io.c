/*
 0 - standard input
 1 - standard output
 2 - standard error
*/

/*
four main operations on file descriptors
file descriptors start at 3 (are non-neg integers)
the first three file descriptors are above...i guess they are a file
the os generates all the tiem and can be looked at by a program...I just got that

open
read
write
close


fd = open(pathname, flags, mode);
num_read = read(fd, buffer, count);
num_written = write(fd, buffer, count);
status = close(fd);
*/


//some includes are needed for these operations
#include <unistd.h> //POSIX header
#include <sys/types.h> //open needs this
#include <sys/stat.h> //open constants defined here
#include <fcntl.h> //file control
#include <stdio.h> //standard input and output libraries
#include <string.h> //C string libraries
#include <strings.h> //string extended functions

//REMEMBER!!!!
//look at the man page for each system call
//man page section 2 for system calls

int main(int argc, char ** argv){

    int fd = open("test.txt", O_WRONLY | O_CREAT, S_IRWXU);
    
    if (fd == -1){
        //fd is -1 for unopened file
    }
    
    int array[] = {1,2,3,4,5};
    
    int num_written = write(fd, array, 5 * sizeof(int));
    
    if (num_written == -1 || num_written != 5*sizeof(int)){
        //the write failed
    }
    printf("%i     ", num_written);
    if (close(fd) != 0){
        //close failed, pretty rare event
    }
    
    fd = open("test.txt", O_RDONLY, S_IRWXU);
    if (fd == -1){
        //fd is -1 for unopened file    
    }
    
    int num_read = read(fd, array, 5 * sizeof(int));
    if (num_read != 5 * sizeof(int)){
        //something went wrong with read
    }
    printf("%i     ", num_read);
    printf("\n");
    for (int i = 0; i<5; i++){
        printf("array[%i]: %i\n", i, array[i]);
    }
    
    close(fd);
    
    return 0;
}

