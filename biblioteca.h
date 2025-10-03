/*Lupsa Alexandra-Cristina - 312CC*/
#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// structura unui arbore binar - din curs
// am adaugat si un camp care leaga arborele binar de cel multicai
typedef struct node
{
	int frecventa;
	char *nume;
	struct node *lt, *rt;
	struct multinode *arbore_multicai;
} TreeNode, *TTree;

// structura pentru Min-Heap - din curs
typedef struct heap
{
	long int maxHeapSize;
	long int size;
	TTree *satelit;
} PrQueue, *APrQueue;

// structuri pentru coada, avem nevoie de ele pentru afisare - din curs
typedef struct cell
{
	TTree satelit;
	struct cell *next;
} QueueCell, *PQueue;

typedef struct queue {
    PQueue front, rear;
} Queue;

// structura pentru a crea mai multi arbori multicai, cu mai multe noduri fii
//
typedef struct multinode
{
	int frecventa;
	char *nume;
	int numar_copii;
	struct multinode **copii;
	struct node *parinte_binar;
} TreeMultiNode, *TMTree;

// FUNCTII PENTRU TOATE CERINTELE (mai putin parcurgeNivel pentru afisare
// CERINTA 1)

// declarare functii arbore binar si coada
void initQueue(Queue *p);
int isEmptyQueue(Queue *p);
void enqueue(TTree a, FILE *f_out, Queue *p);
TTree dequeue(FILE *f_out, Queue *p);
void parcurgeNivel(TTree tree, FILE *f_out, Queue *p);

// declarare functii heap
void PQInit(APrQueue q, int maxSize, FILE *f_out);
TTree buildNod(int frecventa, char *nume, TTree ltree, TTree rtree,
	FILE *f_out);
void SiftDown(APrQueue q, int k, int N);
void SiftUp(APrQueue q, int i);
TTree ExtractMin(APrQueue q);
void Insert(APrQueue q, TTree x);
char *concatenare_nume(TTree a, TTree b);

// CERINTA 2
void parcurgere_codificare_c2(TTree t, char *codificare, FILE *f_out);

// CERINTA 3 & 4
int cauta_nume_substring(TTree t, char *nume);
TTree cautaNod(TTree t, char *nume, char *codificare, int *i);
void prefix_comun(char coduri[][1000], int nr_coduri, char *prefix, int *i);
void parcurgere_codificare_c4(TTree t, char *codificare, FILE *f_out);

// CERINTA 5
TMTree creareconexiuneNod(TTree tree, TMTree mtree, int frecventa, char *nume,
	FILE *f_out);
TMTree cautanod_mtree(TMTree mtree, char *nume, int *distanta);
void adaugare_copil(TMTree mtree, TMTree copil);

// declarare functii de eliberare memorie
void free_arbore_multicai(TMTree mtree);
void free_arbore_binar(TTree t);

#endif