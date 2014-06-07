/* CS261- Assignment 1 - Q.2*/
/* Name: Eric Rouse
 * Date: 10/6/2012
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = 2*(*a);
    /*Set b to half its original value*/
    *b = (*b)/2;
    /*Assign a+b to c*/
    c = *a + *b;
    /*Return c*/
	return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    /*Print the values of x, y and z*/
    printf("The values of x, y and z are: %d, %d and %d, respectively\n", x, y, z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
    int new_z = foo(&x, &y, z);
    /*Print the value returned by foo*/
    printf("foo return value: %d\n", new_z);
    /*Print the values of x, y and z again*/
    printf("The values of x, y and z are: %d, %d and %d, respectively\n", x, y, z);
    /*Is the return value different than the value of z?  Why?*/
    /*the return value is different, because we didn't pass its address to foo.
     * we only passed the value. So the c value of z is a copy of z and it returns
     * that copy. It does not modify z directly as it does x and y.
     */
    return 0;
}
    
    
