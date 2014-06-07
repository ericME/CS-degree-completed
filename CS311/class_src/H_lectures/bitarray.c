#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
/*number of bits in a word*/
#define WORDSIZE 32
/*number of bits needed to represent the value of words*/
#define BITS_WS 7
/*all bits of bits WS set to 1 mask*/
#define MASK 0xFF

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

int main(int argc, char const *argv[])
{
    int *bv, i;
    int s1[] = {UINT_MAX, 5, 0};
    int s2[] = {UINT_MAX, 4, 5, 0};
    int r_check;

    intibv(&bv, UINT_MAX);

    for (i = 0; s1[i]; i++){
        set(bv, s1[i]);
    }

    for (i = 0; s2[i]; i++){
        if (member(bv, s2[i]))
            printf("%u\n", s2[i]);
    }

    free(bv);
    r_check = (float)33/(float)31;
    printf ("%i/%i\t", r_check, (33 == (31*r_check)));
    r_check = (float)35/(float)31;
    printf ("%i/%i\t", r_check, (35 == (31*r_check)));    
    r_check = (float)37/(float)31;
    printf ("%i/%i\t", r_check, (37 == (31*r_check)));   

    return 0;
}

/*
#define ISBITSET(x,i) ((x[i>>3] & (1<<(i&7)))!=0)
#define SETBIT(x,i) x[i>>3]|=(1<<(i&7));
#define CLEARBIT(x,i) x[i>>3]&=(1<<(i&7))^0xFF;

//Structure to hold a single bit

typedef struct {
unsigned int bit : 1;
} Bit;
 
//BitArray structure. 

typedef struct {
Bit bitValues[BIT_ARRAY_LENGTH];
} BitArray; 
*/