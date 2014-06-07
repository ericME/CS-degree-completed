/*
#
#   Name:           Eric Rouse
#   Email Address:  rousee@onid.orst.edu
#   Class Name:     CS311-400
#   Assignment:     Homework #6
#
*/

#include <stdio.h>
#include <sys/times.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <time.h>
#include <sys/stat.h>
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
/*max threads*/
#define MAX_THREADS 30

/*the upper limit for the search set to UINT_MAX for default*/
unsigned int prime_limit = UINT_MAX;     
/* number of threads, set to 1 for default*/
int num_threads = 1;
/*semaphore lock*/
sem_t this_lock; 
/*the search function for each thread*/
void *test(void*);
/*function to find the next number to check*/
unsigned int getNextCandidate(); 
/*function to lock semaphore*/
void lock(); 
/*function to unlock semaphore*/
void unlock(); 
/*initializes a bit vector, returns 1 if memory allocation was successful*/
int initbv(int **bv, unsigned int val);
/*sets a particular value in the bit vector*/
void set(int bv[], unsigned int i);
/*check if a value is part of bit vector*/
int member(int bv[], unsigned int i);



unsigned int next_candidate = 3;  /*next odd number*/
int primes_in_array = 1;  /*number of prime numbers in the array*/
int *bv; /*pointer to bit vector*/




int main(int argc,char *argv[])
{ 
    /* init/dec vars */
    char opt;
    int t, th;
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
                num_threads = strtol(optarg, (char**)NULL, 10);
                break;
            case '?':
                printf("******error******\n");
            default:
                printf("bad input detected\n");
                exit(EXIT_FAILURE);
        }

     /* Initialize bit vector*/
     initbv(&bv, UINT_MAX);

     
     /* Create the lock */
     sem_init(&this_lock, 0, 1); /* create semaphore*/

     /* Create the threads */
     if(num_threads > MAX_THREADS) num_threads = MAX_THREADS;
     pthread_t threads[num_threads];

     /* Start the threads */
     
     for(t=0;t<num_threads;t++)
     {   
         th = pthread_create(&threads[t], NULL, test, NULL);
         if (th)
         {
              perror("pthread_create");
              exit(EXIT_FAILURE);
         }
     }

     /*let the threads have a chance to get started*/
     sleep(1);

   
    /* Join the threads after they are done*/
     t = t-1 ; /*correct the t value before next loop*/
     for(t=t;t > 0;t--)
     {
         th = pthread_join(threads[t], NULL);
         if (th)
         {
              perror("pthread_join");
              exit(EXIT_FAILURE);
         }
     }
     
     
     
     
     /*print primes to std out*/
     if(!quiet_mode){
      printf("2\n");
      for (i = 3; i < prime_limit; i+=2)
       {
          if (member(bv, i))
              printf("%u\n", i);  
       }
     }
     pthread_exit(NULL);
     return 0;
}

void* test(void *dummy)
{
    
     /*keep checking until the limit is reached*/
     while (next_candidate <= prime_limit )
     {       
          unsigned int i = 3;
          unsigned int this_next_candidate = getNextCandidate();
          unsigned int root = sqrt(this_next_candidate) + 2;
      
          /* unlock the next_candidate reading*/
          unlock();
          int is_prime = 1;  /* assuming next_candidate is prime until i say otherwise*/
          
          while (i < root)
          {
              /*loop through, skipping non-primes*/
              if (member(bv,i) != 0){
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

              set(bv, this_next_candidate);  
              primes_in_array ++; 
          
          /*unlock prime list update*/
              unlock();                
          }
          
     }
     return (void*)NULL;
}

/* atomiclly read the next_candidate */
unsigned int getNextCandidate(void)
{
     lock();
     /*CALLING ROUTINE MUST UNLOCK!!!!*/
     unsigned int x = next_candidate;
     next_candidate = next_candidate + 2;
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

/*initializes a bit vector, returns 1 if memory allocation was successful*/
int initbv(int **bv, unsigned int val){
    *bv = calloc(val/WORDSIZE + 1, sizeof(unsigned int));
    return *bv != NULL;
}
/*sets a particular value in the bit vector*/
void set(int bv[], unsigned int i){
    bv[i>>BITS_WS] |= (1 << (i & MASK));
}
/*check if a value is part of bit vector*/
int member(int bv[], unsigned int i){
    return bv[i>>BITS_WS] & (1 << (i & MASK));
}