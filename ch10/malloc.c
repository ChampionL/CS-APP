#include <stdlib.h>
#include "mm.h"
#include "memlib.h"

/*Basic constants and macros*/
#define WSIZE	4		// word size(bytes)
#define DSIZE	8		// double word size(byte)
#define CHUNKSIZE (1<<12)	// inital heap size
#define OVERHEAD 8

#define MAX(x, y) ((x) > (y)? (x):(y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size) | (alloc))

/*Read and write a word at address p*/
#define GET(p)	(*(size_t *)(p))
#define PUT(p, val)	(*(size_t *)(p) = (val))

/* Read the size and allocated filed from address p*/
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer*/
#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks*/
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE((char *)(bp) - WSIZE))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE((char *)(bp) - DSIZE))



static void *coalesce(void *bp)
{
   size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
   size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
   size_t size = GET_SIZE(HDRP(bp));

   if(prev_alloc && next_alloc)
      return bp;
   else if(prev_alloc && !next_alloc){
      size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
      PUT(HDRP(bp), PACK(size, 0));
      PUT(FTRP(bp), PACK(size, 0));
      return(bp);
   }
   else if(!prev_alloc && next_alloc){
      size += GET_SIZE(HDRP(PREV_BLKP(bp)));
      PUT(FTRP(bp), PACK(size, 0));
      PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
      return(PREV_BLKP(bp));
   }
   else{
      size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
      PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
      PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
      return(PREV_BLKP(bp));
   }
}


static void *find_fit(size_t asize)
{
 return NULL;
}

static void place(void *bp, size_t asize)
{

}

static void *extend_heap(size_t words)
{
	char *bp;
	size_t size;

	/* Alloc an even numb of words to maintain alignment*/
	size = (words % 2) ? (words + 1)*WSIZE: words * WSIZE;
	if((bp = mem_sbrk(size)) == NULL)
		return NULL;
	
	/* Initialize free block header/footer and the epliogue head*/
	PUT(HDRP(bp), PACK(size, 0)); //free block header
	PUT(HDRP(bp), PACK(size, 0)); // free bock footer
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); //new epliogue header

	/* coalesce if the previous block was free*/
	return coalesce(bp);
}
static char *heap_listp;
int mm_init(void)
{
	/* create the initial empty heap */
	if((heap_listp = mem_sbrk(4*WSIZE)) == NULL)	
		return -1;
	
	PUT(heap_listp, 0);
	PUT(heap_listp+WSIZE, PACK(OVERHEAD, 1));
	PUT(heap_listp+DSIZE, PACK(OVERHEAD, 1));
	PUT(heap_listp+WSIZE+DSIZE, PACK(0, 1));
	heap_listp += DSIZE;
	
	/* extend the empty heap with a free block of CHUNKSIZE bytes*/
	if(extend_heap(CHUNKSIZE/WSIZE) == NULL)
		return -1;
	
	return 0;
}


void mm_free(void *bp)
{
	size_t size = GET_SIZE(HDRP(bp));	
	
	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));

	coalesce(bp);
}


void *mm_malloc(size_t size)
{
	size_t asize; //adjusted block size
	size_t extendsize; // amount to extend heap if no fit
	char *bp;

	/* Ignore spurious requests*/
	if(size <= 0)
		return NULL;

	/* Adjust block size to include overhead and a alignment reqs*/
	if (size <= DSIZE)
		asize = DSIZE + OVERHEAD;
	else 
		asize = DSIZE * ((size + (OVERHEAD) + (DSIZE-1))/DSIZE);

	/* Search the free list for a fit*/

	if((bp = find_fit(asize)) != NULL){
		place(bp, asize);
		return bp;
	}

	/* No fit found. Get more memeory and place the bock */
	extendsize = MAX(asize, CHUNKSIZE);
	if((bp = extend_heap(extendsize/WSIZE)) == NULL)
		return NULL;

	place(bp, asize);
	return bp;
}

