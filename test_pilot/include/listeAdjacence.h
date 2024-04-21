#ifndef LADJ_H
#define LADJ_H
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include "list.h"
#include "track.h"

typedef struct cell {
    point head;
    char c;
    int fuel;
    int ax;
    int ay;
    struct cell *next;
} Cell;

typedef struct lnode {
    Cell* next;
    Cell* prev;
    Cell* dijNext;
    Cell* dijPrev;
    int distance;
    int tag;
    int totFuel;
    int totWeight;
} Lnode;

typedef struct ladj {
    int nbNode, nbArc;
    int height, width;
    Lnode* **** node; //[x][y][vx][vy]
    point start[3];
    point finish[INT_MAX];
    int nbFinish;
} Ladj;

Lnode* createLnode(void);


Cell *createCell(point head, int fuel, int ax, int ay, Cell* next);

void freeCells(Cell * c);

int* tag(Ladj* L, point p);

int* distance(Ladj* L, point p);

int* totFuel(Ladj* L, point p);

int* totWeight(Ladj* L, point p);

Cell** next(Ladj* L, point p);

Cell** dijNext(Ladj* L, point p);

Cell** dijPrev(Ladj* L, point p);

Cell** prev(Ladj* L, point p);

int pointInTrack(point p, Ladj* L);

int testPt(Track t, point p, char c);

int reachable1(Track t, point p, point q);

int reachable2(Track t, point p, point q);

int newArc(point h, point t, int fuel, int ax, int ay, Ladj* L);

int newArcDij(point h, point t, int fuel, int ax, int ay, Ladj* L);

#endif