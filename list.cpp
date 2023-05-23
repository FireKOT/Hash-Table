#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#include "config.hpp"
#include "list.hpp"


static const size_t BUF_SIZE = 1;

list_t ListCtor (size_t base_size) {

    int err = 0;
    list_t err_list {
        .data = nullptr,

        .head      = 0,
        .tail      = 0,
        .free      = 0,
 
        .size      = 0,
        .capacity  = 0,
        .base_size = 0,
        .factor    = 0,
 
        .islinear  = 0,
     };

    if (!base_size) base_size = 1;

    node_t *data = (node_t*) calloc(base_size + BUF_SIZE, sizeof(node_t));
    RET_ON_VAL(!data, ERR_NULL_PTR, err_list);

    list_t list = {
        .data      = data,

        .head      = BUF_SIZE,
        .tail      = BUF_SIZE,
        .free      = BUF_SIZE,
 
        .size      = 0,
        .capacity  = base_size,
        .base_size = base_size,
        .factor    = 2,
 
        .islinear  = true,
     };

    err = PrepareData(&list, BUF_SIZE, BUF_SIZE + base_size);
    RET_ON_VAL(err, ERR_NULL_PTR, err_list);

    return list;
}

void ListDtor (list_t *list) {

    size_t id = list->head;
    for (size_t i = 0; i < list->size; i++) {
        size_t next = list->data[id].next;

        list->data[id].value = 0;
        list->data[id].next  = 0;
        list->data[id].prev  = 0;

        id = next;
    }
    free(list->data);

    list->data = nullptr;
}

size_t PushAfter (list_t *list, size_t pos, elem_t value) {

    RET_ON_VAL(!list || pos > BUF_SIZE + list->capacity, ERR_INV_ARG, 0);
    int err = 0;

    size_t free_pos = list->free;
    list->free = list->data[free_pos].next;

    err = ResizeUpIfNeed(list, &free_pos);
    RET_ON_VAL(err, ERR_NULL_PTR, 1);

    size_t next = list->data[pos].next;

    list->data[free_pos].value = value;
    list->data[free_pos].next  = next;
    list->data[free_pos].prev  = pos;

    list->data[pos].next = free_pos;
    list->data[next].prev = free_pos;

    if (pos == list->tail) list->tail = free_pos;
    else list->islinear = false;

    list->size++;

    return free_pos;
}

size_t PushBefore (list_t *list, size_t pos, elem_t value) {

    RET_ON_VAL(!list || pos > BUF_SIZE + list->capacity, ERR_INV_ARG, 0);
    int err = 0;

    size_t free_pos = list->free;
    list->free = list->data[free_pos].next;

    err = ResizeUpIfNeed(list, &free_pos);
    RET_ON_VAL(err, ERR_NULL_PTR, 1);

    size_t prev = list->data[pos].prev;

    list->data[free_pos].value = value;
    list->data[free_pos].next  = pos;
    list->data[free_pos].prev  = prev;

    list->data[prev].next = free_pos;
    list->data[pos].prev  = free_pos;

    if (pos == list->head) list->head = free_pos;
    list->islinear = false;

    list->size++;

    return free_pos;
}

size_t PushTail (list_t *list, elem_t value) {

    return PushAfter(list, list->tail, value);
}

size_t PushHead (list_t *list, elem_t value) {

    return PushBefore(list, list->head, value);
}

elem_t ListPop (list_t *list, size_t pos) {

    RET_ON_VAL(!list || pos > BUF_SIZE + list->capacity, ERR_INV_ARG, 0);

    elem_t value = list->data[pos].value;
    size_t next  = list->data[pos].next;
    size_t prev  = list->data[pos].prev;

    list->data[prev].next = next;
    list->data[next].prev = prev;

    if (pos == list->tail) list->tail = prev;
    else if (pos == list->head) list->head = next;
    else list->islinear = false;

    list->data[pos].value = 0;
    list->data[pos].next  = list->free;
    list->data[pos].prev  = 0;

    list->size--;
    list->free = pos;

    ResizeDownIfNeed(list);

    return value;
}

void ListPrint (list_t *list) {

    RET_ON_VAL(!list, ERR_INV_ARG, );

    size_t id = list->head;
    for (size_t i = 0; i < list->size; i++) {
        printf("%ld: %s\n", i, list->data[id].value);
        id = list->data[id].next;
    }
    printf("\n");
}

int PrepareData (list_t *list, size_t start, size_t end) {

    RET_ON_VAL(!list, ERR_NULL_PTR, 1);

    for (size_t i = start; i < end-1; i++) {
        list->data[i].value = 0;
        list->data[i].next  = i+1;
        list->data[i].prev  = 0;
    }

    list->data[end-1].value = 0;
    list->data[end-1].next  = 0;
    list->data[end-1].prev  = 0;

    return 0;
}

int ListResizeUp (list_t *list) {

    RET_ON_VAL(!list, ERR_NULL_PTR, 1);

    node_t *data = (node_t*) realloc(list->data, (BUF_SIZE + list->capacity*list->factor) * sizeof(node_t));
    RET_ON_VAL(!data, ERR_NULL_PTR, 1);

    list->data = data;
    PrepareData(list, BUF_SIZE + list->capacity, BUF_SIZE + list->capacity * 2);
    list->capacity *= list->factor;

    return 0;
}

int ResizeUpIfNeed (list_t *list, size_t *free_pos) {

    RET_ON_VAL(!list || !free_pos, ERR_INV_ARG, 1);

    if (*free_pos == 0) {

        *free_pos = list->capacity + BUF_SIZE;
        ListResizeUp(list);
        list->free = list->data[*free_pos].next;
    }

    return 0;
}

int ListResizeDown (list_t *list) {

    RET_ON_VAL(!list, ERR_NULL_PTR, 1);

    node_t *data = (node_t*) realloc(list->data, (BUF_SIZE + list->capacity/list->factor) * sizeof(node_t));
    RET_ON_VAL(!data, ERR_NULL_PTR, 1);

    list->data = data;
    list->capacity /= list->factor;
    PrepareData(list, list->free, BUF_SIZE + list->capacity);

    return 0;
}

int ResizeDownIfNeed (list_t *list) {

    RET_ON_VAL(!list, ERR_INV_ARG, 1);

    if (list->islinear == 1 && list->capacity > list->base_size && list->size * list->factor * list->factor <= list->capacity) {

        ListResizeDown(list);
    }

    return 0;
}