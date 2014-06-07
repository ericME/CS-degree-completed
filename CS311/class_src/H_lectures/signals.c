#define _POSIX_SOURCE
#define _BSD_SOURCE
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

extern void psignal (int sig, const char *msg);
extern const char * const sys_siglist[];

void intr_sig(int signal)
{
    psignal(signal, "Caught it!");
    
    printf("Caught signal %d: %s\n", signal, sys_siglist[signal]);
    
    return;
}

int main(int argc, char ** argv)
{
    struct sigaction s;
    struct sigaction t;
    
    s.sa_handler = intr_sig;
    sigemptyset(&s.sa_mask);
    
    s.sa_flags = 0;
    
    sigaction(SIGINT, &s, &t);
    
    for (;;){
        printf("foring");
        sleep(3);
    }
    
    return 0;

}
