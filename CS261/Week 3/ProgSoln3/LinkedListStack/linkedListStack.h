#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

# define TYPE      int
# define TYPE_SIZE sizeof(TYPE)

struct LinkedList;

struct LinkedList *createLinkedList();
void  deleteLinkedList(struct LinkedList *l);

int   isEmptyLinkedList(struct LinkedList *l);
void  pushLinkedList(struct LinkedList *l, TYPE val);
TYPE  topLinkedList(struct LinkedList *l);
void  popLinkedList(struct LinkedList *l);

#endif

