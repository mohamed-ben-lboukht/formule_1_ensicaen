#include "list.h"

Node* createNode(point value, Node* next) {
    Node* n=(Node*)malloc(sizeof(Node));
    n->data=value;
    n->next=next;
    return n;
}

Stack* createStack() {
    Stack* S = malloc(sizeof(Stack));
    S->last=NULL;
    S->first=NULL;
    S->size=0;
    return S;
}

Queue* createQueue() {
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->last = Q->first = NULL;
    return Q;
}

void pushStack(point value, Stack* S) {
    assert(S != NULL);
    Node* n = createNode(value, NULL);
    if (isEmpty(S)) {
        S->first = S->last = n;
    } else {
        n->next = S->first;
        S->first = n;
    }
    S->size++;
}

void enqueue(point value, Queue* Q) {
    assert(Q != NULL);
    Node* n = createNode(value, NULL);
    if (isEmpty(Q)) {
        Q->first = Q->last = n;
    } else {
        Q->last->next = n;
        Q->last = n;
    }
}

point popStack(Stack* S) {
    assert(S!=NULL );
    Node* first=S->first;
    if (first->next!=NULL) {
        S->first = first->next;
    } else {
        S->first=NULL;
        S->last=NULL;
    }
    point value = first->data;
    free(first);
    S->size--;
    return value;

}

point dequeue(Queue* Q) {
    assert(Q != NULL);
    Node* first = Q->first;
    point value = first->data;
    Q->first = first->next;
    if (Q->first == NULL) {
        Q->last = NULL;
    }
    free(first);
    return value;
}

bool isEmpty(List* L) {
    return L->first == NULL && L->last == NULL;
}

void Free(List* L) {
    assert(L != NULL);
    while (!isEmpty(L)) {
        popStack(L);
    }
    free(L);
}