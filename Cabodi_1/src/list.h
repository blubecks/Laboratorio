/*
 * list.h
 *
 *  Created on: 08/mag/2013
 *      Author: Andrea
 */
#include <stdio.h>
#include <stdlib.h>

#ifndef LIST_H_
#define LIST_H_
typedef struct lista lista_t;
lista_t* ListInit();
int isEmpty(lista_t*);
void ListFree(lista_t*);
lista_t* OrderInsert(lista_t*,void* elemento,int(*cmp)(void*,void*));
void* ExtractElement(lista_t*,int(*cmp)(void*,void*),void*);
void* ExtractMAXElement(lista_t*,int(*cmp)(void*,void*),void*);
void* ExtractMINElement(lista_t*,int(*cmp)(void*,void*),void*);
void * ExtractEqual( lista_t*,int (* cmp)(void *, void *),void*);
#endif /* LIST_H_ */
