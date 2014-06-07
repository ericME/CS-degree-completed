/*
#
#   Name:           Eric Rouse
#   Email Address:  rousee@onid.orst.edu
#   Class Name:     CS311-400
#   Assignment:     Homework #6
#
*/
#include <time.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/times.h>
#include <stdlib.h>
#include <unistd.h> 
#include <semaphore.h> 
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <math.h>
/*number of bits in a word*/
#define WORDSIZE 32
/*number of bits needed to represent the value of words*/
#define BITS_WS 5
/*all bits of bits WS set to 1 mask*/
#define MASK 0xFF
/*max forks*/
#define MAX_FORKS 30

/*the upper limit for the search set to UINT_MAX for default*/
unsigned int prime_limit = UINT_MAX;     
/* number of forks, set to 1 for default*/
int num_forks = 1;
/*semaphore lock*/
sem_t this_lock; 
/*the search function for each thread*/
void test(void * addr, void * cand);
/*function to find the next number to check*/
unsigned int getNextCandidate(void * cand); 
/*function to lock semaphore*/
void lock(); 
/*function to unlock semaphore*/
void unlock(); 
/*initializes a bit vector shared memory object*/
void initbv();
/*sets a particular value in the bit vector*/
void set(void * addr, unsigned int i);
/*check if a value is part of bit vector*/
int member(void * addr, unsigned int i);



unsigned int next_candidate = 3;  /*next odd number*/
int primes_in_array = 1;  /*number of prime numbers in the array*/



int fd;
size_t size = (UINT_MAX/WORDSIZE + 1) * sizeof(unsigned int);
void * addr;
void * cand;



int main(int argc,char *argv[])
{ 
    /* init/dec vars */
    char opt;
    int f;
    int i;
    int quiet_mode = 0;


    /*
       use getopt to parse command line options
       pull in the options from the command line
       convert the numbers to longs using strtol
       acceptable options:
       -q; turn on quiet_mode, so output is not printed to std_out
       -m; maximum prime
       -c; number of treads
    */
    while ((opt = getopt (argc,argv,"qm:c:"))!= -1)
        switch (opt){
            case 'q':
                quiet_mode = 1; 
                break;
            case 'm':
                prime_limit = strtol(optarg, (char**)NULL, 10)+1;
                break;
            case 'c':
                num_forks = strtol(optarg, (char**)NULL, 10);
                break;
            case '?':
                printf("******error******\n");
            default:
                printf("bad input detected\n");
                exit(EXIT_FAILURE);
        }

     /* Initialize bit vector*/
     initbv();
     
     /* Create the lock */
     sem_init(&this_lock, 0, 1); /* create semaphore*/

     /* Create the forks */
     if(num_forks > MAX_FORKS) num_forks = MAX_FORKS;

     /* Start the forks */
     
     for(f=0;f<num_forks;f++)
     {   
        switch(fork()){
            case -1:
                perror("fork");
                shm_unlink("shm_file");
                shm_unlink("shm_candidate");
                exit(EXIT_FAILURE);
            case 0:
                sleep(1);
                fd = shm_open("shm_file", O_RDWR, 0);
                if ( fd == -1){
                  perror("shm_open, child");
                  shm_unlink("shm_file");
                  shm_unlink("shm_candidate");
                  exit(EXIT_FAILURE);
                }
                addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
                if (addr == MAP_FAILED){
                  perror("mmap, child");
                  shm_unlink("shm_file");
                  shm_unlink("shm_candidate");
                  exit(EXIT_FAILURE);
                }
                /*printf("Fork f:%d pid:%d addr: %ld \n", f, getpid(), (long)addr);*/
                if (close(fd) == -1){
                  perror("close, child");
                  shm_unlink("shm_file");
                  shm_unlink("shm_candidate");
                  exit(EXIT_FAILURE);
                }
                fd = shm_open("shm_candidate", O_RDWR, 0);
                if ( fd == -1){
                  perror("shm_open, child");
                  shm_unlink("shm_candidate");
                  shm_unlink("shm_file");
                  exit(EXIT_FAILURE);
                }
                cand = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
                if (cand == MAP_FAILED){
                  perror("mmap, child");
                  shm_unlink("shm_candidate");
                  shm_unlink("shm_file");
                  exit(EXIT_FAILURE);
                }
                /*printf("Fork f:%d pid:%d addr: %ld \n", f, getpid(), (long)addr);*/
                if (close(fd) == -1){
                  perror("close, child");
                  shm_unlink("shm_candidate");
                  shm_unlink("shm_file");
                  exit(EXIT_FAILURE);
                }
                test(addr, cand);
                exit(EXIT_SUCCESS);
            default:
                break;

        }
     }

     /*let the forks have a chance to get started*/
     
     sleep(5);

   
    /* Wait for the forks after to be done*/
     f = f-1 ; /*correct the f value before next loop*/
     for(f=f;f > 0;f--)
     {
         wait(NULL);
     }
     
     
     /*print primes to std out*/
     if(!quiet_mode){
      printf("2\n");
      for (i = 3; i < prime_limit; i+=2)
       {
          if (member(addr, i))
              printf("%u\n", i);  
       }
     }

     shm_unlink("shm_file");
     shm_unlink("shm_candidate");
     return 0;
}

void test(void * addr, void * cand)
{
    
     /*keep checking until the limit is reached*/
     while (next_candidate <= prime_limit )
     {       
          unsigned int i = 3;
          unsigned int this_next_candidate = getNextCandidate(cand);
          unsigned int root = sqrt(this_next_candidate) + 2;
      
          /* unlock the next_candidate reading*/
          unlock();
          int is_prime = 1;  /* assuming next_candidate is prime until i say otherwise*/
          /*printf("%d  ", this_next_candidate);*/
          while (i < root)
          {
              /*loop through, skipping non-primes*/
              if (member(addr, i) != 0){
                /*prime detected, chech candidate for primitdue*/
                if( this_next_candidate % i == 0  )
                {
                    is_prime = 0; /*not a prime number  */
                    break;
                }
              }   
              i+=2;   
          }
          if (is_prime == 1) /*add it to the list*/
          {
          /*lock for prime list update*/
              lock();
 
          /*update prime list*/

              set(addr, this_next_candidate);  
              primes_in_array ++;
          /*unlock prime list update*/
              unlock();                
          }

     }
     return;
}

/* atomiclly read the next_candidate */
unsigned int getNextCandidate(void * cand)
{
     unsigned int x;
     lock();
     /*CALLING ROUTINE MUST UNLOCK!!!!*/
     memcpy(&x, cand, sizeof(unsigned int));
     next_candidate = x + 2;
     memcpy(cand, &next_candidate, sizeof(unsigned int));
     return x;
}
/* set sem_wait and its error checking*/
void lock(void)
{
    if (sem_wait(&this_lock) == -1) 
    {
          perror("Semaphore invalid");
          exit(EXIT_FAILURE);
    }
}
/* set sem_post and its error checking*/
void unlock(void)
{
    if (sem_post(&this_lock) == -1) 
    {
          perror("Semaphore invalid");
           exit(EXIT_FAILURE);
    }
} 

/*initializes a bit vector shared memory object*/
void initbv(void){
     /*create shared memory objects*/
    fd = shm_open("shm_file", O_CREAT | O_EXCL | O_RDWR | O_TRUNC, 0777);
    if ( fd == -1){
      perror("shm_open file");
      shm_unlink("shm_file");
      shm_unlink("shm_candidate");
      exit(EXIT_FAILURE);
    }
    if ( ftruncate(fd, size) == -1){
      perror("ftruncate");
      shm_unlink("shm_file");
      shm_unlink("shm_candidate");
      exit(EXIT_FAILURE);
    }
    addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if ( addr == MAP_FAILED){
      perror("mmap");
      shm_unlink("shm_file");
      shm_unlink("shm_candidate");
      exit(EXIT_FAILURE);
    }
    if ( close(fd) == -1){
      perror("close");
      shm_unlink("shm_file");
      shm_unlink("shm_candidate");
      exit(EXIT_FAILURE);
    }
    fd = shm_open("shm_candidate", O_CREAT | O_EXCL | O_RDWR | O_TRUNC, 0777);
    if ( fd == -1){
      perror("shm_open candidate");
      shm_unlink("shm_candidate");
      shm_unlink("shm_file");
      exit(EXIT_FAILURE);
    }
    if ( ftruncate(fd, sizeof(unsigned int)) == -1){
      perror("ftruncate");
      shm_unlink("shm_candidate");
      shm_unlink("shm_file");
      exit(EXIT_FAILURE);
    }
    cand = mmap(NULL, sizeof(unsigned int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if ( cand == MAP_FAILED){
      perror("mmap");
      shm_unlink("shm_candidate");
      shm_unlink("shm_file");
      exit(EXIT_FAILURE);
    }
    if ( close(fd) == -1){
      perror("close");
      shm_unlink("shm_candidate");
      shm_unlink("shm_file");
      exit(EXIT_FAILURE);
    }
    memcpy(cand, &next_candidate, sizeof(unsigned int));
    return;
}
/*sets a particular value in the bit vector*/
void set(void * addr, unsigned int i){
    char * ptr = (i >> 3) + addr;
    *ptr |= (1 << (i % 8));
}
/*check if a value is part of bit vector*/
int member(void * addr, unsigned int i){
    char * ptr = (i >> 3) + addr;
    return *ptr & (1 << (i % 8));
}