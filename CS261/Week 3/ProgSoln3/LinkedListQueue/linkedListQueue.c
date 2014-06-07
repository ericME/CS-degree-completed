#include "linkedListQueue.h"
#include "assert.h"
#include <stdlib.h>



struct Link {
	TYPE          val;
	struct Link *next;
};


/* Singly Linked List with Head and Tail */
struct ListQueue {
   struct Link *head;
   struct Link *tail;
};



/* List queue with a sentinel at the front */

void initListQueue (struct ListQueue *q) {
   struct Link *lnk = (struct Link *) malloc(sizeof(struct Link));
   assert(lnk != 0); 
   lnk->next = 0;
   q->tail = q->head = lnk;
}




struct ListQueue *createListQueue()
{
	struct ListQueue *newList = malloc(sizeof(struct ListQueue));
	initListQueue(newList);
	return newList;
}

void _freeListQueue(struct ListQueue *l) {
  while (!isEmptyListQueue(l))
  {
     removeFrontListQueue(l);
  }
}

void deleteListQueue(struct ListQueue *l)
{
	_freeListQueue(l);
	free(l);
}



void addBackListQueue (struct ListQueue *q, TYPE e) {
   struct Link * lnk = (struct Link *) malloc(sizeof(struct Link));
   assert(lnk != 0);

   lnk->next = 0;
   lnk->val = e;

   q->tail->next = lnk; /* we know it has a tail*/
   q->tail = lnk;
}


TYPE frontListQueue (struct ListQueue *q) {
   assert(!isEmptyListQueue(q));
   return q->head->next->val;
}


void removeFrontListQueue (struct ListQueue *q) {
   struct Link *tlnk;
   assert(! isEmptyListQueue(q));
  	
   tlnk = q->head->next; 
   q->head->next = q->head->next->next;
   
   if(q->head->next == 0)
   	q->tail = q->head;

   free(tlnk);  /* release the memory!*/
}

int isEmptyListQueue (struct ListQueue *q) {
   return (q->head->next == 0);
}

