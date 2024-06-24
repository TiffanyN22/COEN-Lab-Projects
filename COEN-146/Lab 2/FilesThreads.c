//Name: Tiffany Nguyen
//Date: April 10, 2024
//Title: Lab 2 - Multi-threading (Step 1)
//Description: The purpose of this lab is to use multithreading to copy data from multiple files 
// at the same time
//Run: compile, then pass in src.dat files followed by dest.dat files (should have same number of files)


#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>  // malloc(), free()
#include <pthread.h> // pthread_create()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // open(), close()
#include <errno.h>   // errno
#include <time.h>    // clock()

#define BUF_SIZE 2048 //buffer size

// data structure to hold copy
struct copy_struct {
	int thread_id; 
	char* src_filename;
	char* dst_filename; 
};

// copies a files from src_filename to dst_filename using functions fopen(), fread(), fwrite(), fclose()
int func_copy(char* src_filename, char* dst_filename) {
	FILE *src, *dst;
	src = fopen(src_filename, "r");	// opens a file for reading
	if (src == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		exit(0);
	}
	dst = fopen(dst_filename, "w");	// opens a file for writing; erases old file/creates a new file
	if (dst == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		exit(0);
	}

	char* buf = malloc((size_t)BUF_SIZE);  // allocate a buffer to store read data
	
	// reads content of file with loop iterations until end of file
	while (!feof(src)) {
        	// read the data, exit if nothing is read
        	if(!fread(buf, 1, 1, src)){
        		break;
        	}
                // writes bytes_read to dst_filename
        	fwrite(buf, 1, 1, dst);
        }
	// closes src file pointer
	fclose(src);
	// closes dst file pointer
	fclose(dst);
	// frees memory used for buf
	free(buf);
	return 0;
}

// thread function to copy one file
void* copy_thread(void* arg) {
	struct copy_struct params = *(struct copy_struct*)arg;  // cast/dereference void* to copy_struct
	printf("thread[%i] - copying %s to %s\n", params.thread_id, params.src_filename, params.dst_filename);
	//call file copy function using passed in parameters
	func_copy(params.src_filename, params.dst_filename);	
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	 // check correct usage of arguments in command line, should have even numbers of files after first parameter
	 if (argc % 2 != 1) {  
		fprintf(stderr, "usage: %s <n connections> ........\n", argv[0]);
		exit(1);
	}
	char* src_filename;
	char* dst_filename;
	char* src_filenames[argc/2]; // array of source files
	char* dst_filenames[argc/2]; // array of desintation files
	int num_threads; // number of threads to create

	//read all files
	num_threads = argc/2; //divide argc to get num of source files, floored so ignore 1st parameter
	int j;
	for(j = 1; j <= num_threads; j++){
		src_filenames[j-1] = argv[j]; //src is one position after current (because of 1st parameter)
		dst_filenames[j-1] = argv[j + num_threads]; //dest is the num_threads apart from source becuase list all sources together 
	}
	
	pthread_t threads[num_threads]; //initialize threads
	struct copy_struct thread_params[num_threads]; // structure for each thread
	int i;
	for (i = 0; i < num_threads; i++) {
		// initialize thread parameters
		thread_params[i].thread_id = i;
		thread_params[i].src_filename = src_filenames[i];
		thread_params[i].dst_filename = dst_filenames[i];

		// create each copy thread
		pthread_create(threads + i, NULL, copy_thread, thread_params+i);
	}

	// wait for all threads to finish
	for (i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
	}
	pthread_exit(NULL);
}
