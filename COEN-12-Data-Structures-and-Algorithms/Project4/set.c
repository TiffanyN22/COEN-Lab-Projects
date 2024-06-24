/*
 * File: Set.c
 * Author: Tiffany Nguyen
 * Date: November 4, 2022
 * Description: This file implements a set as a hash table that uses 
 * chaining with a circular, doubly linked list and includes function
 * to use the hash table, including createSet, destroySet, numElements,
 * addElement, removeElement, findElement, and getElements.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"
#include "list.h"

struct set{
	int count;
	int length;
	struct list **lists;
	unsigned (*hash)();
	int (*compare)();	
};

/*
 * Function: createSet
 * Complexity: O(n)
 * Description: Returns a pointer to an empty set that acts as a hash table
 * that uses chaining.It sets count to 0, length to maxElts, compare to 
 * the passed in compare function, hash to the passed in hash function, and 
 * creates a linked list using struct list for each index of the hash function 
 */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
	SET *set;
	set = malloc(sizeof(SET));
	assert(set != NULL);

	set->count = 0;
	set->length = maxElts;
	set->compare = compare;
	set->hash = hash;
	
	set->lists = malloc(sizeof(LIST*) * maxElts);
	int i;
	for(i = 0; i < maxElts; i++){
		set->lists[i] = createList(compare);
	}
	
	return set;
}

/*
 * Function: destroySet
 * Complexity: O(n)
 * Description: Deallocates the previously allocated memory for the passed in
 * set, including the memory with each linked list
 */
void destroySet(SET *sp){
	int i;
	for(i = 0; i < sp->length; i++){
		destroyList(sp->lists[i]);
	}
	free(sp->lists);
	free(sp);	
}

/*
 * Function: numElements
 * Complexity: O(1)
 * Description: returns the number of elements in the set passed in
 */
int numElements(SET *sp){
	assert(sp != NULL);
	return sp->count;	
}

/*
 * Function: addElement
 * Complexity: O(n)
 * Description: adds elt to the passed in set by hashing set to the proper
 * index, then adding it to the very end of the linked list if it is not
 * already present
 */
void addElement(SET *sp, void *elt){
	assert(sp != NULL && sp->lists != NULL);
	assert(elt != NULL);
	int hashedIndex = (*sp->hash)(elt)%sp->length;	
	if(findItem(sp->lists[hashedIndex], elt) == NULL){
		addLast(sp->lists[hashedIndex], elt);
		sp->count++;
	}	
}

/*
 * Function: removeElement
 * Complexity: O(n)
 * Description: removes elt from sp by hashing it to an index and calling
 * removeItem to search through the linked list to remove elt 
 */
void removeElement(SET *sp, void *elt){
	assert(sp != NULL && sp->lists != NULL);
	assert(elt != NULL);
	int hashedIndex = (*sp->hash)(elt)%sp->length;
	removeItem(sp->lists[hashedIndex], elt);	
	sp->count--;
}

/*
 * Function: findElement
 * Complexity: O(n)
 * Description: finds elt in sp by hashing to get elt's index and 
 * using findItem to search the linked list.  It returns the element if
 * it is found and NULL if the element is not in the sp.
 */
void *findElement(SET *sp, void *elt){
	assert(sp != NULL && sp->lists != NULL);
	assert(elt != NULL);
	int hashedIndex = (*sp->hash)(elt)%sp->length;
	return findItem(sp->lists[hashedIndex], elt);
}

/*
 * Function: getElements
 * Complexity: O(n^2)
 * Description: returns an array of elements in sp by copying all the 
 * elements in each linked list
 */
void *getElements(SET *sp){
	assert(sp != NULL && sp->lists != NULL);
	
	void **dupSet = malloc(sizeof(void*) * sp->count);
	assert(dupSet != NULL);
	
	int i;
	int dupSetIndexAdjust = 0;
	void **copyCurrentList;
	for(i = 0; i < sp->length; i++){
		copyCurrentList = getItems(sp->lists[i]);
		memcpy(dupSet + dupSetIndexAdjust, copyCurrentList, sizeof(void *) * numItems(sp->lists[i]));
		dupSetIndexAdjust += numItems(sp->lists[i]);
		free(copyCurrentList);
	}
	return dupSet;
}
