#ifndef _LIST_HPP_
#define _LIST_HPP_


#include <stdio.h>


typedef const char* elem_t;


struct node_t {

    elem_t value;

    size_t next;
    size_t prev;
};

struct list_t {

    node_t *data;

    size_t head;
    size_t tail;
    size_t free;

    size_t size;
    size_t capacity;
    size_t base_size;
    size_t factor;

    int islinear;
};


list_t ListCtor (size_t base_size = 2);
void   ListDtor (list_t *list);

size_t PushAfter     (list_t *list, size_t pos, elem_t value);
size_t PushBefore    (list_t *list, size_t pos, elem_t value);
size_t PushTail      (list_t *list, elem_t value);
size_t PushHead      (list_t *list, elem_t value);
elem_t ListPop       (list_t *list, size_t pos);

int ListResizeUp     (list_t *list);
int ResizeUpIfNeed   (list_t *list, size_t *free_pos);
int ListResizeDown   (list_t *list);
int ResizeDownIfNeed (list_t *list);
int PrepareData      (list_t *list, size_t start, size_t end);

void ListPrint (list_t *list);


#endif