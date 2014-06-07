/*
#
#   Name:           Eric Rouse
#   Email Address:  rousee@onid.orst.edu
#   Class Name:     CS311-400
#   Assignment:     Homework #5
#
*/
#ifndef __LISTDEQUE_H
#define __LISTDEQUE_H

# ifndef TYPE
# define TYPE      char*
# define TYPE_SIZE sizeof(char*)
# endif
# ifndef LT
# define LT(A, B) ((A) < (B))
# endif

# ifndef EQ
# define EQ(A, B) ((A) == (B))
# endif

struct linkedList;

struct linkedList *createLinkedList(void);

struct mbuf {
    long mtype;
    char mtext[100];

};


void printList(struct linkedList* lst);
int sizeofList(struct linkedList* lst);

int     isEmptyList(struct linkedList *lst);
void addBackList(struct linkedList *lst, TYPE e);
void    addFrontList(struct linkedList *lst, TYPE val);
void    addSorted(struct linkedList *lst, TYPE e);
void dupList(struct linkedList *lst, struct linkedList *dup);

TYPE  frontList(struct linkedList *lst);
TYPE    backList(struct linkedList *lst);

void  removeFrontList(struct linkedList *lst);
void    removeBackList(struct linkedList *lst);
void sendList(struct linkedList* lst, int i, int msqid, struct mbuf * m_toParent);



#endif

