#include "linkedList.h"

// prints the entire LinkedList
void display()
{
    if(head==NULL)
    {
        printf("Linked List is Empty\n");
        return;
    }
        printf("LinkedList: ");
    struct node* ptr = head;
    while(ptr!=NULL) // start from first node
    {
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

// to insert node at end of LinkedList
void insert_end(int val)
{
    struct node* temp;
        //creating new node
    temp = (struct node*)malloc(sizeof(struct node));
    temp->data = val;
    temp->next = NULL;
    if(head==NULL)
    {
        head = temp; //if list is empty, we return
            return;
    }
    else{
        struct node* ptr = head;
        while(ptr->next!=NULL)
        {
            ptr = ptr->next;
        }
               // tail node pointing to new node
        ptr->next = temp;
    }
}
// to delete first node of LinkedList
void delete_begin()
{
    if(head==NULL) //if List is empty we return
    {
        printf("Linked List is empty | Nothing to delete \n");
        return;
    }
    else
    {
        struct node* ptr = head;
        head = head->next; // head node pointing to second node
        free(ptr); // deleting prev head node
        //printf("Node Deleted \n");
    }
}
