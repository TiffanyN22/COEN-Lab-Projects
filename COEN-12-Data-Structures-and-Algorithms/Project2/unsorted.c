/*
 * File Name: unsorted.c
 * Author: Tiffany Nguyen
 * Date: September 30, 2022
 * Description: This projects implements a set abstract data type for
 * strings.  This particular implementation uses an unsorted array to store the
 * elements, and includes functions for search, insertion, deletion, etc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "set.h"

struct set{
	int count; //number of elements in array
	int length; //length of allocated array
	char **data; //allocated array of elements
};

/*
 * Function: search (private)
 * Complexity: O(n)
 * Description: Use sequential search to check if ELT is present in SET 
 * and return its location if present, and -1 if it is not present
 */

static int search(SET *set, char *elt){
	int i;
	for(i=0; i < set->count; i++){
		if(strcmp(set->data[i], elt) == 0){
			return i;
		}
	}
	return -1; 
}

/*
 * Function: createSet
 * Complexity: O(1)
 * Description: return a pointer to a new set with a maximum of capactiy of MaxElts
 */
SET *createSet(int maxElts){
	SET *sp;

	sp = malloc(sizeof(SET));
	assert(sp != NULL);

	sp->data = malloc(sizeof(char *) *maxElts);
	assert(sp->data != NULL);

	sp->count = 0;
	sp->length = maxElts;

	return sp;
}

/*
 * Function: destorySet
 * Complexity: O(n)
 * Description:  Deallocate memory associated with the set pointed to be SP
 */

void destroySet(SET *sp){
	int i;
	for(i = 0; i < sp->count; i++){
		free(sp->data[i]);
	}
	free(sp->data);
	free(sp);
}

/*
 * Function: numElements
 * Complexity: O(1)
 * Description: return the number of elements in the set pointed to by sp
 */
int numElements(SET *sp){
	return sp->count;
}

/*
 * Function: addElement
 * Complexity: O(n)
 * Description: add elt to the set pointed to by sp if elt is not already in sp
 */
void addElement(SET *sp, char *elt){
	assert(sp != NULL);
	assert(sp->data != NULL);
	assert(sp->count < sp->length); 
	if(search(sp, elt) == -1){
		sp->data[sp->count++] = strdup(elt);
	}
}

/*
 * Function: removeElement
 * Complexity: O(n) 
 * Description: remove elt from the set pointed to by sp
 */
void removeElement(SET *sp, char *elt){
	assert(sp != NULL);
	assert(sp->data != NULL);
	int index = search(sp, elt);
	if(index != -1){
		free(sp->data[index]);
		sp->data[index] = sp->data[--sp->count];
	}
}

/*
 * Function: findElement
 * Complexity: O(n)
 * Description: if elt is present in the set pointed to by sp then return 
 * the matching element, otherwise return NULL
 */
char *findElement(SET *sp, char *elt){
	assert(sp != NULL);
	assert(sp->data != NULL);
	int index = search(sp, elt);
	if(index == -1){
		return 	NULL;
	} else{
		return sp->data[index];
	}
}

/*
 * Function: getElements
 * Complexity: O(n) 
 * Description: allocate and return an array of elements in the set pointed to
 * by sp
 */
char **getElements(SET *sp){
	assert(sp != NULL);
	assert (sp->data != NULL);

	char **copyData;
	copyData = malloc(sizeof(char*) * sp->count);
	assert(copyData != NULL);

	memcpy(copyData, sp->data, sizeof(char*) * sp->count);
	return copyData;	
}
