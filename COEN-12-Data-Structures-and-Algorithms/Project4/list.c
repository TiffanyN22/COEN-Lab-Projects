/*
 * File Name: list.c
 * Author: Tiffany Nguyen
 * Date: October 28, 2022
 * Description: This file implements a circular, doubly linked list using
 * a struct list that includes variables to hold the number of nodes, the
 * head node, and a compare function.  Each node will hold data of any type,
 * a pointer of the next node in the linked list, and a pointer to the
 * previous node 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

struct list{
	int count;
	struct node *head;
	int (*compare)();
};

struct node{
	void *data;
	struct node *next;
	struct node *prev;
};

/*
 * Function: createList
 * Complexity: O(1)
 * Description: Returns a pointer to an empty list with the count set to 0 and
 * the compare function set to the passed in compare function
 */ 
extern LIST *createList(int (*compare)()){
	LIST *list;
	
	list = malloc(sizeof(LIST));
	assert (list != NULL);

	list->count = 0;
	
	list->head = malloc(sizeof(struct node));
	assert(list->head != NULL);
	list->head->next = list->head;
	list->head->prev = list->head;

	list->compare = compare;

	return list;
}

/*
 * Function: destroyList
 * Complexity: O(n)
 * Description: frees the memory associated with the passed in list
 */ 
extern void destroyList(LIST *lp){
	assert(lp != NULL);
	while(lp->head->next != lp->head){
		struct node *nextAfterDelete = lp->head->next->next;
		free(lp->head->next);
		lp->head->next = nextAfterDelete;
	}
	free(lp->head);
	free(lp);	
}

/*
 * Function: numItems
 * Complexity: O(1)
 * Description: returns the count of the passed in list
 */
extern int numItems(LIST *lp){
	return lp->count;
}

/*
 * Function: addFirst
 * Complexity: O(1)
 * Description: creates a node with its data set to the passed in item and
 * inserts it after the head pointer while adjusting the next/prev so that
 * the rest of the linked list isn't lost
 */
extern void addFirst(LIST *lp, void *item){
	assert(lp != NULL);
	assert(item != NULL);

	struct node *dummyNode = lp->head;
	assert(dummyNode != NULL);
	
	struct node *addedNode = malloc(sizeof(struct node));
	assert(addedNode != NULL);
	
	addedNode->data = item;
	
	addedNode->next = dummyNode->next;
	addedNode->prev = dummyNode;
	dummyNode->next->prev = addedNode;
	dummyNode->next = addedNode;

	lp->count++;
}

/*
 * Function: removeFirst
 * Complexity: O(1)
 * Description: Deletes the first node in the passed in list, which includes 
 * adjusting the surrounding node's next/prev pointers, and returns a pointer
 * to the deleted node's data
 */
extern void *removeFirst(LIST *lp){
	assert(lp != NULL);

	struct node *dummyNode = lp->head;
	assert(dummyNode != NULL);
	struct node *deletedNode = dummyNode->next;
	assert(deletedNode != NULL);

	void *deletedData =  deletedNode->data;

	dummyNode->next = deletedNode->next;
	dummyNode->next->prev = dummyNode;
	free(deletedNode);
	lp->count--;

	return deletedData;	
}

/*
 * Function: addLast
 * Complexity: O(1)
 * Description: adds a node to the very end of the circularly linked list using
 * the passed in list's head's previous, sets the data of the new node to item,
 * and adjusts the surrounding node's next/prev pointers
 */
extern void addLast(LIST *lp, void *item){
	assert (lp != NULL);
	assert (item != NULL);

	struct node *dummyNode = lp->head;
	assert(dummyNode != NULL);

	struct node *addedNode = malloc(sizeof(struct node));
	assert(addedNode != NULL);

	addedNode->data = item;

	addedNode->prev = dummyNode->prev;
	addedNode->next = dummyNode;
	dummyNode->prev->next = addedNode;
	dummyNode->prev = addedNode; 

	lp->count++;
}

/*
 * Function: removeLast
 * Complexity: O(1)
 * Description: removes the last node in the passed in list, adjusts the 
 * surrounding nodes' prev/next pointers, and returns the deleted node's data 
 */
extern void *removeLast(LIST *lp){
	assert(lp != NULL);

	struct node *dummyNode = lp->head;
	assert(dummyNode != NULL);
	struct node *deletedNode = dummyNode->prev;
	assert (deletedNode != NULL);

	void *deletedData = deletedNode->data;

	dummyNode->prev = deletedNode->prev;
	dummyNode->prev->next = dummyNode;
	free(deletedNode);
	
	lp->count--;

	return deletedData;
}

/*
 * Function: getLast
 * Complexity: O(1)
 * Description: return the data of the last pointer in the linked list 
 */
extern void *getLast(LIST *lp){
	assert(lp != NULL);
	struct node *lastNode = lp->head->prev;
	assert (lastNode != NULL);
	
	return lastNode->data;	
}

/*
 * Function: removeItem
 * Complexity: O(n)
 * Description: loops through the list until it finds the passed in item
 * and deallocates the memory associated with the item.  It also adjusts
 * the next/prev pointer of the surrounding nodes so that nothing gets
 * lost
 */
extern void removeItem(LIST *lp, void *item){
	assert(lp != NULL);
	struct node *currentNode = lp->head->next;
	while(currentNode != lp->head){
                if((*lp->compare)(currentNode->data, item)==0){
			currentNode->prev->next = currentNode->next;
			currentNode->next->prev = currentNode->prev;
			free(currentNode);			
			lp->count--;
			break;
		}
                currentNode = currentNode->next;
        }
}

/*
 * Function: findItem
 * Complexity: O(n)
 * Description: loops through the passed in list until it finds item,
 * when it would return the data at that node.  If item is not in the list,
 * it returns null
 */
extern void *findItem(LIST *lp, void *item){
	assert(lp != NULL);
        struct node *currentNode = lp->head->next;
        while(currentNode != lp->head){
                if((*lp->compare)(currentNode->data, item)==0){
                        return currentNode->data;
                }
                currentNode = currentNode->next;
        }
	return NULL;
}

/*
 * Function: getItems
 * Complexity: O(n)
 * Description: returns an array of all the elements in the passed in list
 */
extern void *getItems(LIST *lp){
	assert(lp != NULL);

	void **dupList;
        dupList = malloc(sizeof(void*) * lp->count);
        assert(dupList != NULL);
	int dupIndex = 0;

	struct node *currentNode = lp->head->next;
        while(currentNode != lp->head){
		dupList[dupIndex] = currentNode->data;		
		dupIndex++;
		currentNode = currentNode->next;
	}
	return dupList;
}
