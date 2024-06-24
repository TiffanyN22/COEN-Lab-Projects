CC      = gcc
CFLAGS  = -g -Wall
PROGS   = insertionSort mergeSort quickSort

all:    $(PROGS)

clean:; $(RM) $(PROGS) *.o core

insertionSort: insertionSort.o
		$(CC) -o insertionSort insertionSort.o

mergeSort: mergeSort.o
	$(CC) -o mergeSort mergeSort.o

quickSort: quickSort.o
	$(CC) -o quickSort quickSort.o
