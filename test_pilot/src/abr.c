#include<stdio.h>
#include<stdlib.h>
#include "abr.h"

nodeABR *insert(nodeABR *n, point p, int x) {
    if (n == NULL) {
        n = (nodeABR *) malloc(sizeof(nodeABR));
        if (n == NULL) {
            fprintf(stderr, "Failed to allocate memory.\n");
            return NULL;
        }
        n->weight = x;
        n->point = p;
        n->left = NULL;
        n->right = NULL;
    } else if (x < n->weight) {
        n->left = insert(n->left, p, x);
    } else {
        n->right = insert(n->right, p, x);
    }
    return n;
}

nodeABR *extractMin(nodeABR *p, point *pt) {

    nodeABR *q;
    if (p->left == NULL) {
        q = p;
        *pt = p->point;
        p = p->right;
        free(q);
    } else {
        p->left = extractMin(p->left, pt);
    }
    return p;
}

