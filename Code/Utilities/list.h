#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 104

typedef struct Cords {
    int x;
    int y;
} Cords;

typedef struct List {
    Cords cords[MAX_SIZE];
    int head; // indice primo elem libero
    int tail; // indice ultimo elemento inserito
    int length;
} List;


void stampa(List list);
void initList(List* list);
void push(List* list, int _x, int _y);
void pop(List* list);
Cords getElem(List list, int n);
Cords getFirstElem(List list);
Cords getLastElem(List list);

#endif /* _LIST_H */
