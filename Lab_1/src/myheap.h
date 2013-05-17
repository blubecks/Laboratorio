/*
 * myheap.h
 *
 *  Created on: 08/mag/2013
 *      Author: Andrea
 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#ifndef MYHEAP_H_
#define MYHEAP_H_


typedef enum
{
    first_fit,
    best_fit,
    wors_fit
} heap_policy_t;

typedef struct heap_s heap_t;

heap_t *heapCreate (size_t );
void heapDestroy (heap_t *);
void *heapAlloc (heap_t *, size_t);
void heapFree (heap_t *, void *);
void heapSetPolicy (heap_t *, heap_policy_t);
void heapDefrag (heap_t *);
void *heapNewPointer (heap_t *, void *);
void heapDefragClose (heap_t *);


#endif /* MYHEAP_H_ */
