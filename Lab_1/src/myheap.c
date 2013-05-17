/*
 * myheap.c
 *
 *  Created on: 08/mag/2013
 *      Author: Andrea
 */

#include "myheap.h"
int compare_by_size(void*,void*);
int compare_by_offset(void*,void*);

typedef struct sector
{
	int offset;
	size_t dimen;

}sector_t;
struct heap_s
{
    lista_t *empty ;
    lista_t *full;
    size_t dim;
    void *base;
    heap_policy_t policy;
};

heap_t *heapCreate (size_t heapSize)
{
    heap_t *new_heap;
    sector_t *s0;
    new_heap = (heap_t*)malloc(sizeof(heap_t));
    if(new_heap == NULL)
    {
        printf("Error during heap allocation\n");
        exit(EXIT_FAILURE);
    }
    new_heap->empty=ListInit();
    new_heap->full=ListInit();
    new_heap->dim=heapSize;
    new_heap->base=malloc(heapSize);//memoria dello heap allocata
    if(new_heap->base == NULL)
    {
        printf("Error during base allocation\n");
        exit(EXIT_FAILURE);
    }
    s0=(sector_t*)malloc(sizeof(sector_t));
    if(s0==NULL) return NULL;
    s0->offset=(int)new_heap->base;
    s0->dimen=heapSize;
    new_heap->empty = OrderInsert(new_heap->empty,(void*)s0,NULL);//inserisco in empty la partizione intera
    return(new_heap);
}
void heapDestroy (heap_t *h)
{
    ListFree(h->empty);
    ListFree(h->full);
    free(h->base);
    free(h);
    return;
}

void *heapAlloc (heap_t *h, size_t size)
{
	sector_t *s;
	void*item=NULL;
	char*p;
	void*off;
	if(h->dim<size)
	{
		printf("the sector is too big\n");
		return NULL;
	}

	if(h->policy==first_fit)s=(sector_t*)ExtractElement(h->empty,compare_by_size,(void*)item);
	if(h->policy==best_fit) s=(sector_t*)ExtractElement(h->empty,compare_by_size,(void*)size);
	if(h->policy==wors_fit)

    return h->base;
}

void heapSetPolicy (heap_t *h, heap_policy_t policy)
{
	h->policy=policy;
}

int compare_by_size(void*A,void*B)
{
	sector_t * a=(sector_t*) A;
	sector_t * b=(sector_t*) B;
	return(a->dimen-b->dimen);
}
int compare_by_offset(void*A,void*B)
{
	sector_t * a=(sector_t*) A;
	sector_t * b=(sector_t*) B;
	return(a->offset-b->offset);

}
