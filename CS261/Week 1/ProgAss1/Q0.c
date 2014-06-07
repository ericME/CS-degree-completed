/* CS261- Assignment 1 - Q. 0*/
/* Name: Eric Rouse
 * Date: 10/6/2012
 * Solution description: addresses and values
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
     printf("iptr value is: %d\n", *iptr);
     /*Print the address pointed to by iptr*/
     printf("address iptr points to is: %p\n", iptr);
     /*Print the address of iptr itself*/
     printf("iptr address is: %p\n", &iptr);
}

int main(){
    
    /*declare an integer x*/
    int x;
    /*print the address of x*/
    printf("The address of x is: %p\n",&x);
    /*Call fooA() with the address of x*/
    fooA(&x);
    /*print the value of x*/
    printf("The value of x is: %d\n", x);
    return 0;
}
