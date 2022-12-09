#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Cords {
    int x;
    int y;
} Cords;

struct listitem {
    Cords cords;
    struct listitem *next;
};

typedef struct listitem Listitem;


struct list {
    Listitem *head;
};

typedef struct list List;

void initlist (List *); /* initialize an empty list */
void insertfront(List *, Cords newCords); /* insert val at front */
void insertback(List *, Cords newCords); /* insert val at back */
int length(List); /* returns list length */
void destroy(List *); /* deletes list */
void setitem(List *, int n, Cords newCords);/* modifies item at n to val*/
Cords getitem(List, int n); /* returns value at n*/
void removeLastItem(List *);

#endif /* _LIST_H */
