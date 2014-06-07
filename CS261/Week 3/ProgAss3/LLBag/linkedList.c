#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>




/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink * next;
	struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};


/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
*/

void _initList (struct linkedList *lst) {
	//first allocate memory for the first and last links (struct DLink)
	lst->firstLink = (struct DLink*)malloc(sizeof(struct DLink));
	assert(lst->firstLink != 0);
	lst->lastLink = (struct DLink*)malloc(sizeof(struct DLink));
	assert(lst->lastLink != 0);

	//initialize firstlink prev and lastlink next and size to zero
	lst->firstLink->prev = 0;
	lst->lastLink->next = 0;
	lst->size = 0;

	//initialize firstlink to point to lastlink && vice versa
	lst->firstLink->next = lst->lastLink;
	lst->lastLink->prev = lst->firstLink;

}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_addLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
	//temp val
	struct DLink * newItem = malloc(sizeof(struct DLink));
	assert(newItem != 0);
	//new Item properties
	newItem->next = l;
	newItem->prev = l->prev;
	newItem->value = v;
	//update l and whatever was before l
	l->prev->next = newItem;
	l->prev = newItem;
	//update size
	lst->size++;
}


/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addFrontList(struct linkedList *lst, TYPE e)
{
	_addLinkBefore(lst, lst->firstLink->next, e);
}

/*
	addBackList
	param: lst the linkedList
	pre: lst is not null
	post: lst is not empty
*/

void addBackList(struct linkedList *lst, TYPE e){
	_addLinkBefore(lst, lst->lastLink, e);
}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct linkedList *lst) {
	return(lst->firstLink->next->value);
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/

TYPE backList(struct linkedList *lst)
{
	return(lst->lastLink->prev->value);
}

/*
	_removeLink
	param: lst the linkedList
	param: l the linke to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
*/

void _removeLink(struct linkedList *lst, struct DLink *l)
{
	l->prev->next = l->next;
	l->next->prev = l->prev;
	lst->size--;
	//free(l);
}

/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct linkedList *lst) {
	_removeLink(lst, lst->firstLink->next);
}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/

void removeBackList(struct linkedList *lst)
{	
	_removeLink(lst, lst->lastLink->prev);
}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/

int isEmptyList(struct linkedList *lst) {
	if (lst->firstLink->next == lst->lastLink) return(1);
	return(0);
}


/* Function to print list
 Pre: lst is not null
 */
void _printList(struct linkedList* lst)
{
	struct DLink * check = malloc(sizeof(struct DLink));
	assert(check != 0);
	check = lst->firstLink->next;
	while(check != lst->lastLink){
		printf("%d", check->value);
		check = check->next;
	}
	free(check);

}
//BAG INTERFACE
/* Iterative implementation of contains() 
 Pre: lst is not null
 */

void addList(struct linkedList *lst, TYPE v)
{
	_addLinkBefore(lst, lst->firstLink->next, v);
}

/* Iterative implementation of contains() 
 Pre: lst is not null
 pre: list is not empty
 */
int containsList (struct linkedList *lst, TYPE e) {
	//create a temp var
	struct DLink * check = malloc(sizeof(struct DLink));
	assert(check != 0);
	//INITIALIZE IT
	check = lst->firstLink->next;
	//check each one
	while(check != lst->lastLink){
		if(check->value == e) return(1);
		check = check->next;
		if(check == lst->lastLink) return(0);
	}
	//if you love me let me go
	free(check);
	return(0);
}

/* Iterative implementation of remove() 
 Pre: lst is not null
 pre: lst is not empty
 */
void removeList (struct linkedList *lst, TYPE e) {
	//create a temp var
	struct DLink * check = malloc(sizeof(struct DLink));
	assert(check != 0);
	//INITIALIZE IT
	check = lst->firstLink->next;
	while(check != lst->lastLink){
		if(check->value == e){
			_removeLink(lst, check);
			free(check);
			return;
		}
		check = check->next;
	}
	printf("Error; value not found");
	//if you love me let me go
	free(check);
}


