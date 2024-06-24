
/*
 * File Name: sorted.c
 * Author: Tiffany Nguyen
 * Date: October 7, 2022
 * Description: This projects implements a set abstract data type for
 * strings.  This particular implementation uses a sorted array to store the
 * elements, and includes functions for search, insertion, deletion, etc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

struct set{
        int count; //number of elements in array
        int length; //length of allocated array
        char **data; //allocated array of elements
};

/*
 * Function: search (private)
 * Complexity: O(log n)
 * Description: Use binary search to check if ELT is present in SET 
 * and return its location if present, and returns low and alters 
 * the value the found pointer points to to false if it is not present
 */

static int search(SET *set, char *elt, bool *found){
	assert(set != NULL);
	assert (set->data != NULL);

	int high = set->count - 1;
	int low = 0;
	int mid;

	while(low <= high){
		mid = (low + high)/2;
		if (strcmp(set->data[mid], elt) == 0){
			*found = true;
			return mid;
		}
		else if (strcmp(set->data[mid], elt) > 0){
			high = mid - 1;
		}
		else {
			low = mid + 1;			
		}
	}
	*found = false;
        return low;
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
 * Description: add elt to its correct position in the set pointed to by sp 
 * if elt is not already in sp
 */
void addElement(SET *sp, char *elt){
        assert(sp != NULL);
        assert(sp->data != NULL);
        assert(sp->count < sp->length);
        
	bool found = false;
	int index = search(sp, elt, &found); 
	if(found == false){
		int i;
		for (i = sp->count - 1; i >= index; i--){
			sp->data[i+1] = sp->data[i];
		}
                sp->data[index] = strdup(elt);
		sp->count++;
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
        
	bool found = false;
	int index = search(sp, elt, &found);
	if(found == true){
		free(sp->data[index]);
		int i;
		for(i = index; i < sp->count - 1; i++){
			sp->data[i] = sp->data[i+1];
		}
		sp->count--;
	}
}

/*
 * Function: findElement
 * Complexity: O(log n)
 * Description: if elt is present in the set pointed to by sp then return 
 * the matching element, otherwise return NULL
 */
char *findElement(SET *sp, char *elt){
        assert(sp != NULL);
        assert(sp->data != NULL);
	
	bool found = false;
	int index = search(sp, elt, &found);
	found ? sp->data[index] : NULL;
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
