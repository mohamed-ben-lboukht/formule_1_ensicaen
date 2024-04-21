#ifndef LIST_H
#define LIST_H
#include "point.h"
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    point data;
    struct Node* next;
} Node;

typedef struct stack{
    Node* first;
    Node* last;
    int size;
} List;

typedef List Stack;
typedef List Queue;

Node* createNode(point value, Node* next);

Stack* createStack(void);

Queue* createQueue(void);

void pushStack(point value, Stack*);

void enqueue(point value, Queue*);

point popStack(Stack*);

point dequeue(Queue*);

bool isEmpty(List*);

void Free(List* );


#endif 