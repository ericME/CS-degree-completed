/*	dynArr.c: Dynamic Array implementation. */
#include <assert.h>
#include <stdlib.h>
#include "dynamicArrayDeque.h"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
	int beg;        /* Beginning of the 'floating' array */
};


/* ************************************************************************
	Dynamic Array Functions
************************************************************************ */

/* Initialize (including allocation of data array) dynamic array.

	param: 	v		pointer to the dynamic array
	param:	cap 	capacity of the dynamic array
	pre:	v is not null
	post:	internal data array can hold cap elements
	post:	v->data is not null
*/
void initDynArr(DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v!= 0);
	v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;
	v->beg = 0;

}

/* Allocate and initialize dynamic array.

	param:	cap 	desired capacity for the dyn array
	pre:	none
	post:	none
	ret:	a non-null pointer to a dynArr of cap capacity
			and 0 elements in it.		
*/
DynArr* createDynArr(int cap)
{
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r,cap);
	return r;
}

/* Deallocate data array in dynamic array. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	d.data points to null
	post:	size and capacity are 0
	post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v)
{
	if(v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
	v->beg = 0;
}

/* Deallocate data array and the dynamic array ure. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	the memory used by v->data is freed
	post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

/* Resizes the underlying array to be the size cap 

	param: 	v		pointer to the dynamic array
	param:	cap		the new desired capacity
	pre:	v is not null
	post:	v has capacity newCap
*/
void _dynArrSetCapacity(DynArr *v, int newCap)
{	
	
	int i;
	
	/* Create a new underlying array*/
	TYPE *newData = (TYPE*)malloc(sizeof(TYPE)*newCap);
	assert(newData != 0);
	
	/* copy elements to it */
	//int j = v->beg;
	for(i = 0; i <  v->size; i++)
	{
		newData[i] = v->data[_physicalIndex(v,i)];

	}
	
	for(i = v->size; i < newCap; i++)
		newData[i] = 0;
	
	/* Delete the oldunderlying array*/
	free(v->data);
	/* update capacity and size and data*/
	v->data = newData;
	v->capacity = newCap;
	v->beg = 0;
}

/* Get the size of the dynamic array

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	none
	ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v)
{
	return v->size;
}

/* 	Adds an element to the end of the dynamic array

	param: 	v		pointer to the dynamic array
	param:	val		the value to add to the end of the dynamic array
	pre:	the dynArry is not null
	post:	size increases by 1
	post:	if reached capacity, capacity is doubled
	post:	val is in the last utilized position in the array
*/
void addDynArr(DynArr *v, TYPE val)
{

	addBackDynArr(v, val);

}

/*	Get an element from the dynamic array from a specified position
	
	param: 	v		pointer to the dynamic array
	param:	pos		integer index to get the element from
	pre:	v is not null
	pre:	v is not empty
	pre:	pos < size of the dyn array and >= 0
	post:	no changes to the dyn Array
	ret:	value stored at index pos
*/

TYPE getDynArr(DynArr *v, int pos)
{

   assert(pos < v->size);
   assert(pos >= 0);
   
   return v->data[_physicalIndex(v, pos)];
}

/*	Put an item into the dynamic array at the specified location,
	overwriting the element that was there

	param: 	v		pointer to the dynamic array
	param:	pos		the index to put the value into
	param:	val		the value to insert 
	pre:	v is not null
	pre:	v is not empty
	pre:	pos >= 0 and pos < size of the array
	post:	index pos contains new value, val
*/
void putDynArr(DynArr *v, int pos, TYPE val)
{
	assert(pos < v->size);
	assert(pos >= 0);
	v->data[_physicalIndex(v,pos)] = val;
}

/*	Swap two specified elements in the dynamic array

	param: 	v		pointer to the dynamic array
	param:	i,j		the elements to be swapped
	pre:	v is not null
	pre:	v is not empty
	pre:	i, j >= 0 and i,j < size of the dynamic array
	post:	index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(DynArr *v, int i, int  j)
{

	TYPE  temp;

	assert(i < v->size);
	assert(j < v->size);
	assert(i >= 0);
	assert(j >= 0);

	temp = v->data[_physicalIndex(v,i)];
	v->data[_physicalIndex(v,i)] = v->data[_physicalIndex(v,j)];
	v->data[_physicalIndex(v,j)] = temp;

}

/*	Remove the element at the specified location from the array,
	shifts other elements back one to fill the gap

	param: 	v		pointer to the dynamic array
	param:	idx		location of element to remove
	pre:	v is not null
	pre:	v is not empty
	pre:	idx < size and idx >= 0
	post:	the element at idx is removed
	post:	the elements past idx are moved back one
*/
void removeAtDynArr(DynArr *v, int idx)
{
	/* FIXME: You will write this function */

  int i;

   assert(idx < v->size);
   assert(idx >= 0);

   //Move all elements up

   for(i = idx; i <= v->size-2; i++)
   {
      v->data[_physicalIndex(v,i)] = v->data[_physicalIndex(v,i+1)];
   }

   v->size--;

}



/* ************************************************************************
	Stack Interface Functions
************************************************************************ */

/*	Returns boolean (encoded in an int) demonstrating whether or not the 
	dynamic array stack has an item on it.

	param:	v		pointer to the dynamic array
	pre:	the dynArr is not null
	post:	none
	ret:	1 if empty, otherwise 0
*/
int isEmptyDynArr(DynArr *v)
{
	return !(v->size);
}

/* 	Push an element onto the top of the stack

	param:	v		pointer to the dynamic array
	param:	val		the value to push onto the stack
	pre:	v is not null
	post:	size increases by 1
			if reached capacity, capacity is doubled
			val is on the top of the stack
*/
void pushDynArr(DynArr *v, TYPE val)
{
	addDynArr(v, val);
}

/*	Returns the element at the top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the stack
*/
TYPE topDynArr(DynArr *v)
{
	assert(!isEmptyDynArr(v));
	return v->data[_physicalIndex(v, v->size-1)];
}

/* Removes the element on top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	size is decremented by 1
			the top has been removed
*/
void popDynArr(DynArr *v)
{
	assert(! isEmptyDynArr(v));
	v->size--; 
}

/* ************************************************************************
	Bag Interface Functions
************************************************************************ */

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	v		pointer to the dynamic array
	param:	val		the value to look for in the bag
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the bag
*/
int containsDynArr(DynArr *v, TYPE val)
{
	int i = 0;
	assert(!isEmptyDynArr(v));
   
	for(i = 0; i < sizeDynArr(v); i++)
      if(EQ(v->data[_physicalIndex(v,i)], val) )
         return 1;
      return 0;

}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	v		pointer to the dynamic array
	param:	val		the value to remove from the array
	pre:	v is not null
	pre:	v is not empty
	post:	val has been removed
	post:	size of the bag is reduced by 1
*/
void removeDynArr(DynArr *v, TYPE val)
{
	int i = 0;

	assert(!isEmptyDynArr(v));

	for(i = 0; i < sizeDynArr(v); i++)
      if(EQ(v->data[_physicalIndex(v,i)], val))
      {
           removeAtDynArr(v,i); 
           break;
      }
}


/*
 * Wraps an index from back to front and fron to back
 * param: index
 * pre: -1 <= index <=cap
 * post: 0<= index < cap
 */

int _physicalIndex (DynArr *v , int idx)
{
	int offset = v->beg + idx;
	int absIndex = offset;

	if(offset < 0)
		absIndex = offset + v->capacity;
	if(offset >= v->capacity)
		absIndex = offset - v->capacity;
	return absIndex;
}


/*
 *  Computes the Physical Index given logical index  (e.g. performs wrap around)
 *  param:  v
 *  param:  logincal index
 *  pre: 	v is not null
 *  pre:	0<= logicalIndex < size
 *  post:	none
 */
/*int _physicalIndex(DynArr *v, int lindex)
{
	assert(v!=0);
	return((lindex + v->beg) % v->capacity);
}*/
/* ************************************************************************
 Deque Interface Functions
 *************************************************************************/
void addFrontDynArr(DynArr *v, TYPE val){
	if (v->size >= v->capacity) 
		_dynArrSetCapacity(v, 2*v->capacity);

	v->beg = _physicalIndex(v, -1);
	v->data[v->beg] = val;
	v->size++;
	
}

void removeFrontDynArr(DynArr *v){
	assert (v->size > 0);

	v->beg = _physicalIndex(v, 1);
	v->size--;
}	
	
void addBackDynArr(DynArr *v, TYPE val)
{
	int index;
	if (v->size >= v->capacity)
		_dynArrSetCapacity(v, 2*v->capacity);
	
	index = _physicalIndex(v, v->size);
	v->data[index] = val;
	v->size++;
}

void removeBackDynArr(DynArr *v){
	assert(v->size >  0);
	v->size--;
}

TYPE frontDynArr(DynArr *v){
	assert (v->size > 0);
	return v->data[_physicalIndex(v,0)];
}	
	
	
TYPE backDynArr(DynArr *v){

	int index = _physicalIndex(v, v->size - 1);
	return v->data[index];
	
}

/* Utility function for looking into the array */

void printDynArr(DynArr *v)
{
	int i = 0;
	printf("==================\n");
	for (i = 0; i < v->size; i++)
		printf("V[%d] == %d\n", i, v->data[_physicalIndex(v,i)]);
		   
	printf("==================\n");

	
}
