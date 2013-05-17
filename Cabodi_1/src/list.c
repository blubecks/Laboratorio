/*
 * list.c
 *
 *  Created on: 08/mag/2013
 *      Author: Andrea
 */

#include "list.h"

typedef struct element
{
	void *elem;
	struct element * next;
}element_t;

struct lista
{
	element_t *head;
	element_t *tail;
	int numElem;

};
/*
 * Alloca e inizializza la lista
 * -alloca puntatore testa
 * -alloca puntatore coda
 * -azzera numero di elementi
 * Assegna testa a coda e coda a testa in maniera da creare lista circolare
 *ritorna il nuovo oggetto lista appena creato o NULL in caso di errore
 */
lista_t*ListInit()
{
	lista_t*new = (lista_t*) malloc(sizeof(lista_t));
	if(new==NULL) return NULL;

	new->head=(element_t*)malloc(sizeof(element_t));
	if(new->head==NULL) return NULL;
	new->head->elem=NULL;
	new->tail=(element_t*)malloc(sizeof(element_t));
	if(new->tail==NULL) return NULL;
	new->tail->elem=NULL;
	new->numElem=0;
	new->head=new->tail;
	new->tail=new->head;
	return(new);
}
/*
 * ritorna 1 se lista vuota
 * ritorna 0 se c'è almeno un elem
 */
int isEmpty(lista_t*l)
{
	if(l->head==l->tail)
		return 1;
	return 0;
}
/*
 * Order Insert si occupa di inserimento in lista in 2 modi
 * -NULL:inserimento semplice in testa
 * -comparator:inserisce in maniera ordinata
 *
 * ritorna il puntatore alla lista completata
 */
lista_t* OrderInsert(lista_t*l,void* elemento,int(*cmp)(void*,void*))
{

	element_t *p=l->head;
	element_t *new =(element_t*) malloc (sizeof(element_t));
	if(new == NULL) return NULL;
	new->elem=elemento;
	new->next=NULL;
	if(isEmpty(l))
	{
		l->head->next=new;
		new->next=l->tail;
		l->numElem++;
		return(l);
	}
	else
	{
		if(cmp==NULL)
		{
			//INSERISCO IN TESTA
			new->next=l->head->next;
			l->head->next=new;
			l->numElem++;
			return(l);
		}
		else
		{
			while(cmp(p->next->elem,new->elem)<=0)
				/*
				 * uso p->next->elem cosi p punta nel punto esatto in cui devo inserire
				 */
			{
				p=p->next;
				if(p->next==l->tail)break;
			}
			new->next=p->next;
			p=new;
			l->numElem++;
			return(l);
		}
	}
}
/*
 * FIRST
 */
void* ExtractElement(lista_t*l,int(*cmp)(void*,void*),void *item)
{
	element_t *p,*ext;
	p=l->head;
	if(isEmpty(l)) return NULL;
	if(cmp==NULL)
	{
		//estraggo come coda LIFO,cioè ultimo inserito in testa(testa esclusa)
		p=p->next;
		l->head->next=p->next;
		ext=p;
		free(p);
		l->numElem--;
		return(ext);
	}
	while(cmp(p->next->elem,item)<0)
	{
		p=p->next;
		//scorri
		if(l->head==l->tail)return NULL;
	}
	//arrivo qua p punta al precedente da estrarre
	ext=p->next;
	p->next=ext->next;
	free(p);
	return((void*)ext);
}
/*
 * WORST
 */
void*ExtractMAXElement(lista_t*l,int(*cmp)(void*,void*),void*item)
{
	element_t *p,*ext,*previous;
	ext=NULL;
	int checked = 0;
	int FindFlag=0;
	if(isEmpty(l)) return NULL;
	p=l->head;
	previous=l->head;
	while(checked!=l->numElem)
	{
		if((cmp(p->next->elem,item)>0)&&(cmp(p->next->elem,ext)>0))
		{
			FindFlag=1;
			ext=p->next;
			previous=p;
			p=p->next;
			checked++;
		}
		else
		{
			previous=p;
			p=p->next;
			checked++;
		}
	}
	if(FindFlag==0) return NULL;

	previous->next=p->next;
	l->numElem--;
	free(p);
	free(previous);
	return(ext);
}
/*
 * BEST
 */
void*ExtractMINElement(lista_t*l,int(*cmp)(void*,void*),void*item)
{
	element_t *p,*ext,*previous;
	int checked = 0;
	int FindFlag=0;
	if(isEmpty(l)) return NULL;
	p=l->head;
	previous=l->head;
	ext=p->next->elem;
	while(checked!=l->numElem)
	{
		if((cmp(p->next->elem,item)>=0)&&(cmp(p->next->elem,ext)<0))
		{
			FindFlag=1;
			ext=p->next;
			previous=p;
			p=p->next;
			checked++;
		}
		else
		{
			previous=p;
			p=p->next;
			checked++;
		}
	}
	if(FindFlag==0) return NULL;

	previous->next=p->next;
	l->numElem--;
	free(p);
	free(previous);
	return(ext);
}
void * ExtractEqual( lista_t * l,int (* cmp)(void *, void *),void * item)
{
	element_t * this,*previous;
	int flag=0;
	void * i;
	this=l->head->next;
	previous=l->head;
	while(this!=l->tail)
	{
		if(cmp(this->elem,item)==0)
		{
			flag=1;
			break;
		}
		previous=this;
		this=this->next;
	}
	if(!flag) return NULL;
	previous->next=this->next;
	i=this->elem;
	l->numElem--;
	free(this);
	return i;
}
void ListFree(lista_t*l)
{
	element_t *this, *erasing;
	this=l->head;
	while(this->next!=l->tail){
	erasing=this;
	this=this->next;
	free(erasing->elem);
	free(erasing);
	}
	free(this->elem);
	free(this);
	free(l->tail);
	free(l->head);
	free(l);


}
