#ifndef __LISTQUEUE_H
#define __LISTQUEUE_H

# ifndef TYPE
# define TYPE      int
# define TYPE_SIZE sizeof(int)
# endif
# ifndef LT
# define LT(A, B) ((A) < (B))
# endif

# ifndef EQ
# define EQ(A, B) ((A) == (B))
# endif


struct ListQueue;

void   initListQueue(struct ListQueue *l);
struct ListQueue *createListQueue();
void	deleteListQueue(struct ListQueue *l);
int 	 isEmptyListQueue(struct ListQueue *l);
void   addBackListQueue(struct ListQueue *l, TYPE val);
TYPE   frontListQueue(struct ListQueue *l);
void   removeFrontListQueue(struct ListQueue *l);

#endif

