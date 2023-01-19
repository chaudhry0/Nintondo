#ifndef CODE_UTILITIES_LINKEDLIST_H_
#define CODE_UTILITIES_LINKEDLIST_H_

#include<stdio.h>
#include<stdlib.h>
void display();
void insert_end(int val);
void delete_begin();

struct node* head;
struct node
{
    int data;
    struct node* next;
};

#endif /* CODE_UTILITIES_LINKEDLIST_H_ */
