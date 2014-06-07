#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

int main(int argc, char ** argv){
    pid_t p;
    
    switch((p=fork())){
     case 0:
        //child case
        printf("I am the child, my process ID is %i (%i) \n", getpid(), getppid());
        break;
     case -1:
        //error case
        perror("Could not create child");
        exit(EXIT_FAILURE);
     default:
        //this is the parent case
        printf("I am the parent, my process ID is %i\n", getpid());        
        break;
    }
    
    //both child and parent continue from here
    
    return 0;
}
