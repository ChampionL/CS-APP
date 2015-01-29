/*Basic constants and macros*/
#define WSIZE	4		// word size(bytes)
#define DSIZE	8		// double word size(byte)
#define CHUNKSIZE (1<<12)	// inital heap size
#define OVERHEAD 8

#define MAX(x, y) ((x) > (y) (x):(y))

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

static void *heap_listp;

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

static void *extend_heap(size_t words)
{
	char *bp;
	size_t size;

	/* Alloc an even numb of words to maintain alignment*/
	size = (words % 2) ? (words + 1)*WSIZE: words * WSIZE;
	if((int)(bp = mem_sbrk(size)) < 0)
		return NULL;
	
	/* Initialize free block header/footer and the epliogue head*/
	PUT(HDRP(bp), PACK(size, 0)); //free block header
	PUT(HDRP(bp), PACK(size, 0)); // free bock footer
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); //new epliogue header

	/* coalesce if the previous block was free*/
	return coalesce(bp);
}


