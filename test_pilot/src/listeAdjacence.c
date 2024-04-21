#include "listeAdjacence.h"

Cell *createCell(point head, int fuel, int ax, int ay, Cell *next) {
    Cell *C;
    C = (Cell *) malloc(sizeof(Cell));
    C->head = head;
    C->fuel = fuel;
    C->ax = ax;
    C->ay = ay;
    C->next = next;
    return C;
}

Lnode *createLnode() {
    Lnode *node = (Lnode *) malloc(sizeof(Lnode));
    node->dijNext = NULL;
    node->dijPrev = NULL;
    node->next = NULL;
    node->prev = NULL;
    node->distance = -1;
    node->tag = 0;
    node->totFuel = INT_MAX;
    node->totWeight = INT_MAX;
    return node;
}

void freeCells(Cell *c) {
    if (c != NULL) {
        freeCells(c->next);
        free(c);
    }
}

int *tag(Ladj *L, point p) {
    return &(L->node[p.x][p.y][p.vx + 5][p.vy + 5]->tag);
}

int *distance(Ladj *L, point p) {
    return &(L->node[p.x][p.y][p.vx + 5][p.vy + 5]->distance);
}

int *totFuel(Ladj *L, point p) {
    return &(L->node[p.x][p.y][p.vx + 5][p.vy + 5]->totFuel);
}

int *totWeight(Ladj *L, point p) {
    
    return &(L->node[p.x][p.y][p.vx + 5][p.vy + 5]->totWeight);
}

Cell **next(Ladj *L, point p) {
    
    return &(L->node[p.x][p.y][p.vx + 5][p.vy + 5]->next);
}

Cell **dijNext(Ladj *L, point p) {
    
    return &(L->node[p.x][p.y][p.vx + 5][p.vy + 5]->dijNext);
}

Cell **dijPrev(Ladj *L, point p) {
    
    return &(L->node[p.x][p.y][p.vx + 5][p.vy + 5]->dijPrev);
}

Cell **prev(Ladj *L, point p) {
    return &(L->node[p.x][p.y][p.vx + 5][p.vy + 5]->prev);
}

int pointInTrack(point p, Ladj *L) {
    int x = L->height;
    int y = L->width;
    return (p.x >= 0 && p.y >= 0 && p.x < x && p.y < y);
}

int testPt(Track t, point p, char c) {
    return t->track[p.x][p.y] == c;
}

int reachable1(Track t, point p, point q) {

    int i, j, x1, x2, y1, y2;

    x1 = p.x < q.x ? p.x : q.x;
    x2 = p.x > q.x ? p.x : q.x;

    y1 = p.y < q.y ? p.y : q.y;
    y2 = p.y > q.y ? p.y : q.y;

    for (i = x1; i <= x2; i++) {
        for (j = y1; j <= y2; j++) {
            if (t->track[i][j] == '.') {
                return 0;
            }
        }
    }

    return 1;
}

int reachable2(Track t, point p, point q) {

    int i, x, y;
    int len, dx, dy;
    float fx, fy, deltax, deltay;

    dx = q.x - p.x;
    dy = q.y - p.y;

    len = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    if (len == 0) {
        return t->track[p.x][p.y] != '.';
    }

    fx = p.x + 0.5f;
    fy = p.y + 0.5f;

    deltax = ((float) dx) / len;
    deltay = ((float) dy) / len;

    for (i = 0; i < len; i++) {

        fx += deltax;
        fy += deltay;
        x = (int) fx;
        y = (int) fy;

        if (t->track[x][y] == '.') {
            return 0;
        }
    }
    return 1;
}

int newArc(point h, point t, int fuel, int ax, int ay, Ladj *L) {

    Cell *C;
    C = createCell(h, fuel, ax, ay, *next(L, t));
    *next(L, t) = C;

    C = createCell(t, fuel, ax, ay, *prev(L, h));
    *prev(L, h) = C;

    L->nbArc++;
    return 0;
}

int newArcDij(point h, point t, int fuel, int ax, int ay, Ladj *L) {
    Cell *C;
    C = createCell(h, fuel, ax, ay, *dijNext(L, t));
    *dijNext(L, t) = C;

    free(*dijPrev(L, h));
    *dijPrev(L, h) = createCell(t, fuel, ax, ay, NULL);

    return 0;
}