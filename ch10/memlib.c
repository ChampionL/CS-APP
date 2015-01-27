#include <stdlib.h>

// private global variables
static char *mem_start_brk; 		// points to first byte of the heap
static char *mem_brk;				// points to last byte of the heap
static char *mem_max_addr;			// max virtual address for the heap

/**
 * mem_init initializes the memory system model
 *
 */
void mem_init(int size)
{
	mem_start_brk = (char *)malloc(size*sizeof(char)); // models available VM
	if (mem_start_brk = NULL){
		fprintf(stderr, "malloc memory error!!\n");
	}
 
	mem_brk = mem_start_brk; // heap is initially empty
	mem_max_addr = mem_start_brk + size; // max address for heap
}

/**
 * mem_sbrk simple medel of the sbrk function. Extends the heap by incr bytes
 * and returns the start address of the new area.In this model the heap can't 
 * shrunk.
 *
 */
void *mem_sbrk(int incr)
{
	char *old_sbrk = mem_brk;
	
	if ((incr < 0) || ((mem_brk + incr) > mem_max_addr)){
		errno = ENOMEM;
		return NULL;
	}
	
	mem_brk += incr;
	return old_sbrk;
}

