#include "list.h"


void initlist(List *ilist) {
    ilist->head = 0;
}

void insertfront(List *ilist, Cords newCords) {
    Listitem *newitem;
    newitem = (Listitem *)malloc(sizeof(Listitem));
    newitem->next = ilist->head;
    newitem->cords = newCords;
    ilist->head = newitem;
}

void insertback(List *ilist, Cords newCords) {
    Listitem *ptr;
    Listitem *newitem;
    newitem = (Listitem *)malloc(sizeof(Listitem));
    newitem->cords = newCords;
    newitem->next = 0;
    if (!ilist->head) {
        ilist->head = newitem;
        return;
    }
    ptr = ilist->head;
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = newitem;
}

int length(List ilist){ /* returns list length */
    Listitem *ptr;
    int count = 1;
    if (!ilist.head) return 0;
        ptr = ilist.head;
    while (ptr->next) {
        ptr = ptr->next;
        count++;
    }
    return count;
}

void destroy(List *ilist) { /* deletes list */
    Listitem *ptr1,
    *ptr2;
    if (!ilist->head) return; /* nothing to destroy */
        ptr1 = ilist->head; /* destroy one by one */
    while (ptr1) {
        ptr2 = ptr1;
        ptr1 = ptr1->next;
        free(ptr2);
    }
    ilist->head = 0;
}

void setitem(List *ilist, int n, Cords newCords){
    Listitem *ptr;
    int count = 0;
    if (!ilist->head) return;
        ptr = ilist->head;
    for (count = 0;count < n;count ++) {
        if (ptr) ptr = ptr->next;
        else return;
    }
    if (ptr)
        ptr->cords = newCords;
}

Cords getitem(List ilist, int n) {
    Cords wrongCords;
    wrongCords.x = -5;
    wrongCords.y = -5;
    Listitem *ptr;
    int count = 0;
    if (!ilist.head) return wrongCords;
    ptr = ilist.head;
    if (n==0) return ptr->cords;
    while (ptr->next) {
        ptr = ptr->next;
        count++;
        if (n == count)
            return (ptr->cords);
    }
    return wrongCords;
}

void removeLastItem(List *ilist) {
    Listitem *ptr = ilist->head;
    Listitem *ptrToRemove;
    if (!ptr) return;
    while (ptr->next->next != NULL) {
        ptr = ptr->next;
    }
    ptrToRemove = ptr->next;
    ptr->next = NULL;
    free(ptrToRemove);
}
