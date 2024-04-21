

#ifndef __TP1_H
#define __TP1_H

#include "point.h"

typedef struct nodeABR {
	int weight;
	point point;
	struct nodeABR *left;
	struct nodeABR *right;
} nodeABR;

nodeABR* insert(nodeABR *n, point p, int x);

nodeABR* extractMin(nodeABR* p, point* pt);


#endif
