/*
 * File Name: table.c
 * Author: Tiffany Nguyen
 * Date: October 14, 2022
 * Description: This file implements a structure set as an abstract data
 * type for strings using a hash table, including an array of flags used
 * to indicate whether or not a given index is empty, filled, or had a 
 * deleted value.  There are also functions to use set, including search,
 * createSet, destorySet, numElements, addElement, removeElement, findElement,
 * and getElement.  
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "set.h"

struct set{
	int count;
	int length;
	char **data;
	char *flags;
};

/*
 * Function: strhash
 * Complexity: O(n)
 * Description: Hash function that hashes the passed in string to an index
 */
unsigned strhash(char *s)
{
	unsigned hash = 0;
	while (*s != '\0')
		hash = 31 * hash + *s ++;
	return hash;
}

/*
 * Function: search (private)
 * Complexity: O(n)
 * Description: checks if ELT, the passed in element, is present in set using 
 * linear probing.  It returns the location of elt if present, the first 
 * location it can be inserted if elt is not present, or -1 if elt is not 
 * present and set is full.  It also changes the value of the passed in 
 * found pointer based on whether or not the element was found.
 */

static int search (SET *set, char *elt, bool *found){
	int availableIndex = -1;
	int hashedIndex = strhash(elt) % set->length;
	int i;
	for(i = 0; i < set->length; i++){
		int probedIndex  = (i + hashedIndex) % set->length;
		if(set->flags[probedIndex] == 'E'){
			*found = false;
			if(availableIndex != -1){ //found deleted earlier
				return availableIndex;
			}
			else{
				return probedIndex;
			}			
		}
		else if(set->flags[probedIndex] == 'D'){
			if (availableIndex == -1){ //deleted index not found before
				availableIndex = probedIndex;
			}
		}
		else if(strcmp(set->data[probedIndex],elt) == 0){
                        *found = true;
                        return probedIndex;
                }
	}
	*found = false;
	return availableIndex;
}

/*
 * Function: createSet
 * Complexity: O(n)
 * Description: returns a pointer to a new empty set with the maximum capacity 
 * of MaxElt, all flags default set to E, length set to MaxElts, and count 
 * set to 0
 */
SET *createSet(int maxElts){
        SET *set;

        set = malloc(sizeof(SET));
        assert(set != NULL);
	
	set->flags = malloc(sizeof(char) *maxElts);
        assert(set->flags != NULL);

	set->data = malloc(sizeof(char *) *maxElts);
        assert(set->data != NULL);
	
	int i;
	for(i = 0; i < maxElts; i++){
		set->flags[i] = 'E';
	}

        set->count = 0;
        set->length = maxElts;

        return set;
}

/*
 * Function: destroySet
 * Complexity: O(n)
 * Description: Deallocate memory associated with the set whose address was 
 * passed in
 */
void destroySet(SET *set){
	int i;
	for(i = 0; i < set->count; i++){
		if(set->flags[i] == 'F'){
			free(set->data[i]);
		}
	}
	
	free(set->flags);
	free(set->data);
	free(set);
}

/*
 * Function: numElements
 * Complexity: O(1)
 * Description: return the number of elements in the set passed in
 */
int numElements(SET *sp){
        return sp->count;
}

/*
 * Function: addElement
 * Complexity: O(n)
 * Description: add elt to the set passed in if elt is not already in set
 * and there is still room in set using search()
 */
void addElement(SET *set, char *elt){
        assert(set != NULL);
        assert(set->data != NULL && set->flags != NULL);
	assert(elt != NULL);
	
	bool found = false;
	int availableLocation = search(set, elt, &found);
	if(!found && availableLocation != -1){
		assert(set->count < set->length);
		char* eltValue = strdup(elt);
		assert(eltValue != NULL);
		set->count++;
		set->flags[availableLocation] = 'F';
                set->data[availableLocation] = eltValue;
        }
}

/*
 * Function: removeElement
 * Complexity: O(n) 
 * Description: remove elt from the set passed in and set its flag to 'D' if 
 * elt is in the set
 */
void removeElement(SET *set, char *elt){
	assert(set != NULL);
        assert(set->data != NULL && set->flags != NULL);
        
	bool found = false;
        int eltLocation = search(set, elt, &found);
        if(found){
		set->count--;
                free(set->data[eltLocation]);
                set->flags[eltLocation] = 'D';
        }
}

/*
 * Function: findElement
 * Complexity: O(n)
 * Description: if elt is present in the set passed in, return  the matching 
 * element, otherwise return NULL
 */
char *findElement(SET *set, char *elt){
        assert(set != NULL);
        assert(set->data != NULL);

        bool found = false;
        int foundLocation = search(set, elt, &found);
        if (found){
		return set->data[foundLocation];
	}
	else{
		return NULL;
	}
}

/*
 * Function: getElements
 * Complexity: O(n)
 * Description: returns an array of the elements stored within the passed in set while
 * ignoring empty indices 
 */
char **getElements(SET *set){
        assert(set != NULL);
        assert (set->data != NULL && set->flags != NULL);

        char **duplicateSet;
        duplicateSet = malloc(sizeof(char*) * set->count);
        assert(duplicateSet != NULL);

        int i;
	int duplicateIndex = 0;
	for(i = 0, duplicateIndex; i < set->length; i++){
		if(set->flags[i] == 'F'){
			duplicateSet[duplicateIndex] = set->data[i];
			duplicateIndex++;
		}
	}
        return duplicateSet;
}
