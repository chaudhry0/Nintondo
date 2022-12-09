#include "list.h"

void stampa(List list){
    int i;
    if (list.tail < list.head){
        for (i=list.tail; i<list.head; i++){
            printf("%d : %d\n", list.cords[i].x, list.cords[i].y);
        }
    }
    if (list.tail > list.head){
        for (i=list.tail; i<MAX_SIZE; i++){
            printf("%d : %d\n", list.cords[i].x, list.cords[i].y);
        }
        for (i=0; i<list.head; i++){
            printf("%d : %d\n", list.cords[i].x, list.cords[i].y);
        }
    }
    printf("\n\n");
}


void initList(List* list){
    list->head = 0;
    list->tail = 0;
    list->length = 0;
}

void push(List* list, int _x, int _y){
    if ((list->head + 1 == list->tail) || (list->head == MAX_SIZE - 1 && list->tail == 0)){
        printf("LISTA PIENA\n");
    } else{
        list->cords[list->head].x = _x;
        list->cords[list->head].y = _y;
        list->length++;
        list->head++;
        if (list->head == MAX_SIZE){
            list->head = 0;
        }
    }
}

void pop(List* list){
    if (list->head == list->tail){
        printf("LISTA VUOTA\n");
    } else{
        list->length--;
        list->tail++;
        if (list->tail == MAX_SIZE){
            list->tail = 0;
        }
    }
}

Cords getElem(List list, int n){
    if (list.length > 0 && n <= list.length){
        int index = list.tail + n - 1;
        if (index > MAX_SIZE -1){
            index -= MAX_SIZE;
        }
        return list.cords[index];
    }
    Cords cords;
    cords.x = 1000;
    cords.y = 1000;
    return cords;
}

Cords getFirstElem(List list){
    return getElem(list, 1);
}

Cords getLastElem(List list){
    return getElem(list, list.length);
}
