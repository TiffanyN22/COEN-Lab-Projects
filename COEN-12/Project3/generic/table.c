/*
 * File Name: table.c
 * Author: Tiffany Nguyen
 * Date: October 21, 2022
 * Description: this file implements a structure set as an abstract data type
 * holding a hash table of any generic data type.  Set also includes an array
 * of flags that indicates whether a given index is empty, filled, or held
 * a deleted value, in addition to variables for count, length, the compare
 * function, and the hash function.  This file also implements functions
 * to use set, including search, createSet, destorySet, numElements, 
 * addElement, removeElement, findElement, and getElement. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

struct set{
	int count;
	int length;
	void **data;
	char *flags;
	int (*compare)();
	unsigned (*hash)();
};

/*
 * Function: createSet
 * Complexity: O(n)
 * Description: returns a pointer to an empty set with the maximum capacity of
 * MaxElts, all flags default set to E, compare set to the passed in compare
 * function, hash set to the passed in hash function, length set to maxElts, 
 * and count set to 0
 */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
	SET *set;
	
	set = malloc(sizeof(SET));
	assert(set != NULL);

	set->data = malloc(sizeof(char*) * maxElts);
	assert(set->data != NULL);

	set->flags = malloc(sizeof(char) *maxElts);
	assert(set->flags != NULL);
	int i;
        for(i = 0; i < maxElts; i++){
                set->flags[i] = 'E';
        }

	set->compare = compare;
	set->hash = hash;
	
	set->count = 0;
	set->length = maxElts;

	return set;
}

/*
 * Function: search (private)
 * Complexity: O(n)
 * Description: checks if elt is present using linear probing.  It returns
 * the index of the element if it is present.  Otherwise, it returns the 
 * first location elt can be inserted or -1 if the set is full.  It also
 * updates found based on whether or not elt was found
 */
static int search(SET *set, void *elt, bool *found){
	int availableIndex = -1;
	int hashedIndex = (*set->hash)(elt)%set->length;
	
	int i;
	for(i = 0; i < set->length; i++){
		int probedIndex = (i + hashedIndex) % set->length;
		if(set->flags[probedIndex] == 'E'){
			*found = false;
			if(availableIndex != -1){ //found deleted earlier
                                return availableIndex;
                        }
                        else{
                                return probedIndex;
                        }
		}
		else if (set->flags[probedIndex] == 'D'){
			if (availableIndex == -1){
				availableIndex = probedIndex;
			}
		}
		else if((*set->compare)(set->data[probedIndex], elt) == 0){
			*found = true;
			return probedIndex;
		}
	}
	*found = false;
	return availableIndex;
}

/*
 * Function: destroySet
 * Complexity: O(1)
 * Description: Deallocates the previously allocated memory for the passed
 * in set and its flags and data 
 */
void destroySet(SET *set){
	free(set->flags);
	free(set->data);
	free(set);
} 

/*
 * Function: numElements
 * Complexity: O(1);
 * Description: return the number of elements in the set passed in
 */
int numElements(SET *set){
	return set->count;
}

/*
 * Function: addElement
 * Complexity: O(n)
 * Description: add elt to the set passed in if elt is not already in set
 * and there is still space in set
 */
void addElement(SET *set, void *elt){
        assert(set != NULL);
        assert(set->data != NULL && set->flags != NULL);
        assert(elt != NULL);

        bool found = false;
        int availableLocation = search(set, elt, &found);
        if(!found){
                assert(set->count < set->length);
                set->flags[availableLocation] = 'F';
		set->data[availableLocation] = elt;
                set->count++;
        }
}

/*
 * Function: removeElement
 * Complexity: O(n)
 * Description: set the flag at the location of the passed in element, elt,
 * to 'D' for deleted if elt is in the set
 */
void removeElement(SET *set, void *elt){
	assert(set != NULL);
        assert(set->data != NULL && set->flags != NULL);

        bool found = false;
        int eltLocation = search(set, elt, &found);
        if(found){
                set->flags[eltLocation] = 'D';
                set->count--;
        }

}

/*
 * Function: findElement
 * Complexity: O(n)
 * Description: return the matching element if elt is present in the set passed
 * in and return NULL if it isn't present
 */
void *findElement(SET *set, void *elt){
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
 * Description: returns the elements stored within the passed in set while
 * ignoring empty indices 
 */
void *getElements(SET *set){
        assert(set != NULL);
        assert (set->data != NULL && set->flags != NULL);

        char **dupSet;
        dupSet = malloc(sizeof(char*) * set->count);
        assert(dupSet != NULL);

        int i;
        int dupIndex = 0;
        for(i = 0, dupIndex; i < set->length; i++){
                if(set->flags[i] == 'F'){
                        dupSet[dupIndex] = set->data[i];
                        dupIndex++;
                }
        }
        return dupSet;
}
