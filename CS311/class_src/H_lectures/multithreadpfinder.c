/***************************************
Author: Maan Ashgar
A program to create a list of prime numbers using from 1 to 4 threads
based on user input. to run the program, provid 2 command line numbers 
like this:
     ../exename 4 56   
     where exename is the program name, 
     4 is the number of threads <should be between 1-4> ,
     56 is the limit of the numbers to check the primes in.
This program use threads and semaphores so that it can scheduel the task
of checking the primes between the threads.

The implementation:
    check user input for error;
    if all good, set globle variables;
    create the semaphore and the threads;
           threads start executing test() method;
           each thread get the current next_odd and check if its prime;
           lock the next_odd when reading it and increasing it;
           add next_odd to the list if it is prime, lock the list when doing that;
           threads keeps doing that till the prime_limit is reached
    after threads done, join all threads;
    print the prime list;


*****************************************/

#include <stdio.h>
#include <sys/times.h>
#include <stdlib.h>
#include <unistd.h>
//include the thread library, add -lpthread at compiling
#include <pthread.h> 
//include the semaphore library, add -lrt at compiling
#include <semaphore.h> 

#include <limits.h>
/*number of bits in a word*/
#define WORDSIZE 32
/*number of bits needed to represent the value of words*/
#define BITS_WS 7
/*all bits of bits WS set to 1 mask*/
#define MASK 0xFF



int prime_limit;     // the upper limit for the search
int thread_done_counter = 0; // to check the thread finish job
int num_threads = 1; // number of threads, set to 1 for error avoidance
sem_t my_lock;        // semaphore lock
void *test(void*);  // the search function for each thread
int getNextOdd();
void lock();
void open();
/*initializes a bit vector, returns 1 if memory allocation was successful*/
int intibv(int **bv, unsigned int val);
/*sets a particular value in the bit vector*/
void set(int bv[], unsigned int i);
/*check if a value is part of bit vector*/
int member(int bv[], unsigned int i);



int next_odd = 3;  //next odd number
int primes_in_array = 1;  //number of prime numbers in the array
int *bv; /*pointer to bit vector*/





int main(int argc,char *argv[])
{ 
    //ERROR CHECKING CODE ****************************************************
    /* check the arguments number*/
    if (argc != 3)
    {
       printf("bad arguments, exiting program!");
       exit(-1);         
    }
    
    /* check for the number of threads required, should not exceed 4 
      or less than 1. Use 1 thread as a counter-measure*/
     if (atoi(argv[1]) > 10 || atoi(argv[1]) < 1)
    {
       printf("Invalid number of threads, exiting program!");
       exit(-1);  
    }
    else
    {
        num_threads = atoi(argv[1]); 
    }
    
    /* check for the upper limit of primes, should not < 0  */
     if (atoi(argv[2]) < 1)
    {
       printf("Invalid upper limit for primes, exiting program!");
       exit(-1);         
    }
    //END OF ERROR CHECKING CODE *********************************************
    //if all good, move on
    
    
    //set the upper limit for the prime numbers
     prime_limit = atoi(argv[2]);
     /*put the first primes in the bit vector */

     /*initialize bit vector*/
     intibv(&bv, UINT_MAX);
     set(bv, 2);
     printf("Number of Threads: %d , Prime limit: %d \n", num_threads,prime_limit);
     
     /* Create the lock */
     sem_init(&my_lock, 0, 1); // create semaphore

     /* Create the threads */
     pthread_t threads[num_threads];

     /* Start the threads */
     int t, th;
     for(t=0;t<num_threads;t++)
     {   
         th = pthread_create(&threads[t], NULL, test, NULL);
         if (th)
         {
              printf("ERROR; return code from pthread_create() is %d\n", th);
              exit(-1);
         }
     }

   
    /* Join the threads after they are done*/
     t = t-1 ; // to fix the t value before next loop
     for(t=t;t > 0;t--)
     {
         th = pthread_join(threads[t], NULL);
         if (th)
         {
              printf("ERROR; return code from pthread_join() is %d\n", th);
              exit(-1);
         }
     }
     
     // PRINT THE PRIME LIST ***************************
     
     printf("Prime Numbers %d: ", primes_in_array);
     int i;
     for (i = 2; i < primes_in_array; i++)
     {
        if (member(bv, i))
            printf("%u\t", i);  
     }
     
     printf("\n "); 

     //*****************************************

     pthread_exit(NULL);
     return 0;
}

void* test(void *dummy)
{
     //print the name of the thread entering this method    
     printf("%d I'm in \n",pthread_self()); 
     
     //keep checking until the limit is reached
     while (next_odd < prime_limit )
     {       
          int i = 0;
          unsigned int my_next_odd = getNextOdd();
      
          // unlock the next_odd reading
          open();
          int is_prime = 1;  // assuming next_odd is prime until the loop say otherwise
          
          while (i < primes_in_array && my_next_odd > member(bv, i) && member(bv,i) != 0)
          {
              //if (next_odd/number)*number != next_odd, then number is not a divider 
              int r_check  = (float)my_next_odd / (float)member(bv, i);
              if( my_next_odd == ( member(bv, i)* r_check )  )
              {
                  is_prime = 0; // to signel that it is not a prime number  
                  break;
              }   
              i++;   
          }
           
          if (is_prime == 1) // if its still a prime, add it to the list
          {
          //lock for prime list update
              lock();
 
          //update prime list
              printf("Found: %u by thread: %u\n", my_next_odd,pthread_self());         

              set(bv, my_next_odd);  
              primes_in_array ++; 
          
          //unlock prime list update
              open();                
          }
          
        sleep(1);
     }
     //print the name of the thread exiting this method 
     printf("%d I'm out \n",pthread_self());   
     thread_done_counter++;
}

/* a method to atomiclly read the next_odd */
int getNextOdd()
{
     //lock the next_odd reading
     lock();

     int x = next_odd;
     next_odd = next_odd + 2;
     return x;
     // remeber to unlock after the method call
}
/* to reduce the code lines, this method macro sem_wait and its error checking*/
void lock()
{
    if (sem_wait(&my_lock) == -1) 
    {
          printf("Semaphore invalid");
          exit(2);
    }
}
/* to reduce the code lines, this method macro sem_post and its error checking*/
void open()
{
    if (sem_post(&my_lock) == -1) 
    {
          printf("Semaphore invalid");
           exit(2);
    }
}

/*initializes a bit vector, returns 1 if memory allocation was successful*/
int intibv(int **bv, unsigned int val){
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
