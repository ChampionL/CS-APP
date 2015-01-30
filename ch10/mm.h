#ifndef __MM__H
#define __MM__H
/* $begin mallocinterface */
int mm_init(void); 
void *mm_malloc(size_t size); 
void mm_free(void *bp);
/* $end mallocinterface */

void mm_checkheap(int verbose);
void *mm_realloc(void *ptr, size_t size);

#endif
