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

void sig1_handler(int signal)
{
    printf("SIGUSR1 has been caught\n");
    
}

void sig2_handler(int signal)
{
    printf("SIGUSR2 has been caught\n");

}

void sigi_handler(int signal)
{
    printf("SIGINT has been caught, terminating program\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char ** argv)
{
    /* define/init vars */
    pid_t pid = getpid();
    /* sigaction for SIGUSR1 */
    struct sigaction s1;
    struct sigaction t1;
    /* sigaction for SIGUSR2 */
    struct sigaction s2;
    struct sigaction t2;
    /* sigaction for SIGINT  */
    struct sigaction si;
    struct sigaction ti;
    
    /* set up signal handling SIGUSR1 */
    s1.sa_handler = sig1_handler;
    sigemptyset(&s1.sa_mask);
    
    s1.sa_flags = 0;
    /* set up signal handling SIGUSR2 */
    s2.sa_handler = sig1_handler;
    sigemptyset(&s2.sa_mask);
    
    s2.sa_flags = 0;
    /* set up signal handling SIGINT  */
    si.sa_handler = sigi_handler;
    sigemptyset(&si.sa_mask);
    
    si.sa_flags = 0;
    /* initialize the actions */
    sigaction(SIGINT, &si, &ti);
    sigaction(SIGUSR1, &s1, &t1);
    sigaction(SIGUSR2, &s2, &t2);
    
    /* send messages in order */
    kill(pid, SIGUSR1);
    kill(pid, SIGUSR2);
    kill(pid, SIGINT);
    /* wait to recieve the messages */
    for (;;)
        pause();
    
    return 0;

}
