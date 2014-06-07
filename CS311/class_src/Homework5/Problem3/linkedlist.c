/*
#
#   Name:           Eric Rouse
#   Email Address:  rousee@onid.orst.edu
#   Class Name:     CS311-400
#   Assignment:     Homework #5
#
*/
#include "linkedlist.h"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <math.h>
/*prototypes*/

/* Double Link*/
struct DLink {
    TYPE value;
    long count;
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

void static _initList (struct linkedList *lst) {
   /* create the sentinels */
   lst->firstLink = (struct DLink *) malloc(sizeof(struct DLink));
   lst->lastLink = (struct DLink *) malloc (sizeof(struct DLink));
   assert (lst->firstLink != 0);
   assert (lst->lastLink != 0);
   
   lst->firstLink->prev = 0;
   lst->firstLink->next = lst->lastLink;
   
   lst->lastLink->next = 0;
   lst->lastLink->prev = lst->firstLink;

   lst->size = 0;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList(void)
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

void static _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
   struct DLink * lnk = (struct DLink *) malloc(sizeof(struct DLink));
   assert(lnk != 0);

    lnk->next = l;
    lnk->prev = l->prev;
    lnk->value = malloc(sizeof(char[100]));
    strcpy(lnk->value,v);
    lnk->count = 1;

    l->prev->next = lnk;
    l->prev = lnk;
   
    lst->size++;
}
/*
    addSorted
    param: lst the linkedList
    param: e the element to be added
    pre: lst is not null
    post: lst is not empty, increased size by 1
*/

void addSorted(struct linkedList *lst, TYPE e)
{
    struct DLink *lnk = lst->firstLink->next;
    int cmp;
    
    while(lnk != lst->lastLink)
    {
        cmp = strcmp(lnk->value, e);
        if (cmp < 0){
            lnk = lnk->next;
        }
/*        else if (cmp == 0){
            lnk->count++;
            return;
        }*/
        else {
            break;
        }
    }
    _addLinkBefore(lst, lnk, e);
    
}


/*
    dupList
    param: lst the new linkedList
    param: dup the linkedList to be dup'd
    pre: lst is not null
    post: lst is not empty, increased size by 1
*/

void dupList(struct linkedList *lst, struct linkedList *dup)
{


   lst->firstLink = dup->firstLink;
   lst->lastLink = dup->lastLink;
    
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

void addBackList(struct linkedList *lst, TYPE e) {
    struct DLink *lnk = lst->firstLink->next;
    int cmp;
    
    while(lnk != lst->lastLink)
    {
        cmp = strcmp(lnk->value, e);
        if (cmp < 0){
            lnk = lnk->next;
        }
        else if (cmp == 0){
            lnk->count++;
            return;
        }
        else {
            break;
        }
    }
    _addLinkBefore(lst, lnk, e);
   
}

/*
    frontList
    param: lst the linkedList
    pre: lst is not null
    pre: lst is not empty
    post: none
*/

TYPE frontList (struct linkedList *lst) {
   assert(!isEmptyList(lst));
   return lst->firstLink->next->value;
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
    assert(!isEmptyList(lst));
    return lst->lastLink->prev->value;
}

/*
    _removeLink
    param: lst the linkedList
    param: l the linke to be removed
    pre: lst is not null
    pre: l is not null
    post: lst size is reduced by 1
*/

void static _removeLink(struct linkedList *lst, struct DLink *l)
{

    l->next->prev = l->prev;
    l->prev->next = l->next;
    free(l);
    lst->size--;
}

/*
    removeFrontList
    param: lst the linkedList
    pre:lst is not null
    pre: lst is not empty
    post: size is reduced by 1
*/

void removeFrontList(struct linkedList *lst) {
   assert(! isEmptyList(lst));
    
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
    assert(!isEmptyList(lst));

    _removeLink(lst, lst->lastLink->prev);  
}

/*
    isEmptyList
    param: lst the linkedList
    pre: lst is not null
    post: none
*/

int isEmptyList(struct linkedList *lst) {
   return (lst->firstLink->next == lst->lastLink);
}


/* Function to print list
 Pre: lst is not null
 */
void printList(struct linkedList* lst)
{
    struct DLink *lnk = lst->firstLink->next;
    long spaces;

    while(lnk != lst->lastLink)
    {
        for (spaces = 6 - floor( log10( abs(lnk->count))); spaces > 0; spaces--) printf(" ");
        printf("%ld %s\n", lnk->count, lnk->value);
        lnk = lnk->next;
    }
    
}

/* Function to iterate through the list
 Pre: lst is not null
 */
void sendList(struct linkedList* lst, int i, int msqid, struct mbuf * m_toParent)
{
    struct DLink *lnk = lst->firstLink->next;

    while(lnk != lst->lastLink)
    {
        strcpy(m_toParent->mtext, lnk->value);
        m_toParent->mtype = i;
        /*printf("%s\n", m_toParent->mtext);*/
        msgsnd(msqid, m_toParent, 100, 0);
        lnk = lnk->next;
    }
    
}

int sizeofList(struct linkedList* lst){
    return lst->size;
}