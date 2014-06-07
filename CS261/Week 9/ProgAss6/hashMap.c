#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "hashMap.h"

int stringHash1(char * str)
{
    int i;
    int r = 0;
    for (i = 0; str[i] != '\0'; i++)
        r += str[i];
    return r;
}

int stringHash2(char * str)
{
    int i;
    int r = 0;
    for (i = 0; str[i] != '\0'; i++)
        r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
    return r;
}

void initMap (struct hashMap * ht, int tableSize)
{
    int index;
    
    if(ht == NULL)
        return;
    ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
    ht->tableSize = tableSize;
    ht->count = 0;
    for(index = 0; index < tableSize; index++)
        ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{
    free(ht);
}

/* Adds the provided link */
void _addList(struct hashLink * link, KeyType k, ValueType v)
{
	//temp val and new item val
	struct hashLink * newItem = (struct hashLink *) malloc(sizeof(struct hashLink));
	assert(newItem != 0);
	//new Item properties
	newItem->next = NULL;
	newItem->value = v;
	newItem->key = k;
	//if nothing is there, add the new item
	if (link == NULL){
		//printf("new item \n"); //debug
		link = newItem;
	}
	//find the end of the list
	else{
		while (link->next != NULL){
			link = link->next;
		}
		link->next = newItem;
	}



}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{
	int hash;
    if (HASHING_FUNCTION == 1){
    	hash = stringHash1(k)%ht->tableSize;
    }
    else hash = stringHash2(k)%ht->tableSize;

    if (hash < 0) hash += ht->tableSize;
    //printf("hash: %d\n", hash); //debug

	//temp val and new item val
	struct hashLink * newItem = (struct hashLink *) malloc(sizeof(struct hashLink));
	assert(newItem != 0);
	//new Item properties
	newItem->next = NULL;
	newItem->value = v;
	newItem->key = k;
	//if nothing is there, add the new item
	if (ht->table[hash] == NULL){
		//printf("new item \n"); //debug
		ht->table[hash] = newItem;
	}
	//find the end of the list
	else{
		struct hashLink * link = ht->table[hash];
		while (link->next != NULL){
			link = link->next;
		}
		link->next = newItem;
	}

    //_printList(ht->table[hash]); //debug
    ht->count++;
}

/* Prints all of the map, array by array, link by link */
void printMap(struct hashMap * ht){
	for(int index = 0; index < ht->tableSize; index++){
		struct hashLink * link = ht->table[index];
	        if(ht->table[index] != NULL){
	        	//printf("index: %d \n", index); //debug
	        	printf("%s:  %d\n", ht->table[index]->key, ht->table[index]->value);
	        	while(link->next != NULL){
	        		link = link->next;
	        		printf("%s:  %d\n", link->key, link->value);
	        	}
	        }
	}

}

ValueType* atMap (struct hashMap * ht, KeyType k)
{
	int hash;
    if (HASHING_FUNCTION == 1){
    	hash = stringHash1(k)%ht->tableSize;
    }
    else hash = stringHash2(k)%ht->tableSize;

    if (hash < 0) hash += ht->tableSize;

	struct hashLink * link = ht->table[hash];

	if(ht->table[hash] != NULL){
		if (!(strcmp(link->key, k))) return &link->value;
		while(link->next != NULL){
			link = link->next;
			if (!(strcmp(link->key, k))) return &link->value;
		}
	}
    return NULL;
}

int containsKey (struct hashMap * ht, KeyType k)
{
	int hash;
    if (HASHING_FUNCTION == 1){
    	hash = stringHash1(k)%ht->tableSize;
    }
    else hash = stringHash2(k)%ht->tableSize;

    if (hash < 0) hash += ht->tableSize;
	//printf("hash: %d\n", hash); //debug

	if (ht->table[hash] != NULL){
		struct hashLink * link = ht->table[hash];
		//printf("%s  %s \n", link->key, k); //debug
		if (!(strcmp(link->key, k))) return 1;
    	while(link->next != NULL){
    		link = link->next;
    		if (!(strcmp(link->key, k))) return 1;

    	}
	}

    return 0;
}

void removeKey (struct hashMap * ht, KeyType k)
{
	int hash;
    if (HASHING_FUNCTION == 1){
    	hash = stringHash1(k)%ht->tableSize;
    }
    else hash = stringHash2(k)%ht->tableSize;

    if (hash < 0) hash += ht->tableSize;
	//printf("hash: %d\n", hash); //debug

	if (ht->table[hash] != NULL){
		struct hashLink * link = ht->table[hash];
		//first link
		if (!(strcmp(link->key, k))){
			if (link->next != NULL){
			ht->table[hash] = link->next;
			}
			else ht->table[hash] = NULL;
			ht->count--;
		}
		//subsequent links
		else{
				while(link->next != NULL){


				if (link->next->key == k){

					if(link->next->next != NULL)
						link->next = link->next->next;
					else link->next = NULL;
					ht->count--;
					break;
				}
				link = link->next;
			}
		}
	}
}

int size (struct hashMap *ht)
{
    return ht->count;
}

int capacity(struct hashMap *ht)
{
    return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht)
{
    return (ht->tableSize - ht->count);
}

float tableLoad(struct hashMap *ht)
{
	float load;
	float count = (float)ht->count;
	float size = (float)ht->tableSize;
	load = count/size;
    return load;
}
